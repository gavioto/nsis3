<?php

if ( defined( 'MEDIAWIKI' ) ) {

class SpamBlacklist {
	var $blacklist = false;
	var $previousFilter = false;
	var $files = array();
	var $warningTime = 600;
	var $expiryTime = 900;
	var $warningChance = 100;
	
	function SpamBlacklist( $settings = array() ) {
		global $IP;
		$this->files = array( "http://meta.wikimedia.org/w/index.php?title=Spam_blacklist&action=raw&sb_ver=1" );

		foreach ( $settings as $name => $value ) {
			$this->$name = $value;
		}
	}

	function filter( &$title, $text, $section ) {
		global $wgArticle, $wgDBname, $wgMemc, $messageMemc, $wgVersion, $wgOut;

		$fname = 'wfSpamBlacklistFilter';
		wfProfileIn( $fname );

		# Call the rest of the hook chain first
		if ( $this->previousFilter ) {
			$f = $this->previousFilter;
			if ( $f( $title, $text, $section ) ) {
				wfProfileOut( $fname );
				return true;
			}
		}

		if ( !is_array( $this->files ) ) {
			$this->files = array( $this->files );
		}
		if ( count( $this->files ) == 0 ){ 
			# No lists
			wfProfileOut( $fname );
			return false;
		}

		# Refresh cache if we are saving the blacklist
		$recache = false;
		foreach ( $this->files as $fileName ) {
			if ( preg_match( '/^DB: (\w*) (.*)$/', $fileName, $matches ) ) {
				if ( $wgDBname == $matches[1] && $title->getPrefixedDBkey() == $matches[2] ) {
					$recache = true;
					break;
				}
			}
		}


		if ( $this->blacklist === false || $recache ) {
			if ( !$recache ) {
				$this->blacklist = $wgMemc->get( "spam_blacklist_blacklist" );
			}
			if ( !$this->blacklist ) {
				# Load lists
				$lines = array();
				wfDebug( "Constructing spam blacklist\n" );
				foreach ( $this->files as $fileName ) {
					if ( preg_match( '/^DB: (\w*) (.*)$/', $fileName, $matches ) ) {
						if ( $wgDBname == $matches[1] && $title->getPrefixedDBkey() == $matches[2] ) {
							$lines = array_merge( $lines, explode( "\n", $text ) );
						} else {
							$lines = array_merge( $lines, $this->getArticleLines( $matches[1], $matches[2] ) );
						}
					} elseif ( preg_match( '/^http:\/\//', $fileName ) ) {
						# HTTP request
						# To keep requests to a minimum, we save results into $messageMemc, which is
						# similar to $wgMemc except almost certain to exist. By default, it is stored
						# in the database
						#
						# There are two keys, when the warning key expires, a random thread will refresh
						# the real key. This reduces the chance of multiple requests under high traffic 
						# conditions.
						$key = "spam_blacklist_file:$fileName";
						$warningKey = "$wgDBname:spamfilewarning:$fileName";
						$httpText = $messageMemc->get( $key );
						$warning = $messageMemc->get( $warningKey );

						if ( !is_string( $httpText ) || ( !$warning && !mt_rand( 0, $this->warningChance ) ) ) {
							wfDebug( "Loading spam blacklist from $fileName\n" );
							$httpText = $this->getHTTP( $fileName );
							$messageMemc->set( $warningKey, 1, $this->warningTime );
							$messageMemc->set( $key, $httpText, $this->expiryTime );
						}
						
						$lines = array_merge( $lines, explode( "\n", $httpText ) );
					} else {
						$lines = array_merge( $lines, file( $fileName ) );
					}
				}

				# Strip comments and whitespace, then remove blanks
				$lines = array_filter( array_map( 'trim', preg_replace( '/#.*$/', '', $lines ) ) );

				# No lines, don't make a blacklist which will match everything
				if ( count( $lines ) == 0 ) {
					wfDebug( "No lines\n" );
					$this->blacklist = false;
				} else {
					$this->blacklist = $lines;
				}
				$wgMemc->set( "spam_blacklist_blacklist", $this->blacklist, 3600 );
			}
		}

		$retVal = false;

		if ( $this->blacklist ) {
			# Do the match
			#wfDebug( "Checking text against blacklist: {$this->blacklist}\n" );

			foreach ( $this->blacklist as $badurl ) {
				if ( stristr( $text, $badurl ) ) {
					$pattern  = '/' . preg_quote('http', '/') . 's?' . preg_quote('://', '/');
					$pattern .= '[a-z0-9\-\.]*' . preg_quote($badurl, '/') . '/i';
					if ( preg_match( $pattern, $text ) ) {
						wfDebug( "Match!\n" );
						EditPage::spamPage( $badurl );
						$retVal = true;
						break;
					}
				}
			}
		}

		wfProfileOut( $fname );
		return $retVal;
	}

	function getArticleLines( $db, $article ) {
		$row = wfMsgForContent($article);
		if ( $row ) {
			return explode( "\n", $row );
		} else {
			return array();
		}
	}

	function getHTTP( $url ) {
		// Use wfGetHTTP from MW 1.5 if it is available
		include_once( 'HttpFunctions.php' );
		if ( function_exists( 'wfGetHTTP' ) ) {
			$text = wfGetHTTP( $url );
		} else {
			$url_fopen = ini_set( 'allow_url_fopen', 1 );
			$text = file_get_contents( $url );
			ini_set( 'allow_url_fopen', $url_fopen );
		}
		return $text;
	}
}

	
} # End invocation guard
?>

