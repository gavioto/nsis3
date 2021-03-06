<?

// Regenerating can take a while
set_time_limit(300);

include_once(dirname(__FILE__)."/engine/nsisweb.pkg.php");

$nsisweb->start_page('Regenerating Content',FALSE);
echo '<span class="atitle">Regenerate Content</span>';

$session = $nsisweb->get_session();
$user    = find_userid($session->user_id);

if(!$user->is_admin()) {
  echo '<p>This page is for users with admin rights only.</p>';
  } else {
  $result = $nsisweb->query("select pageid from nsisweb_pages",__FILE__,__LINE__);
  if($result && $nsisweb->how_many_results($result)>0) {
    while($record = $nsisweb->get_result_array($result)) {
      $pages[] = $record['pageid'];
    }
    print '<p>Found '.count($pages).' to regenerate.<br><br></p><ul>';
    foreach($pages as $pageid) {
      $page = find_pageid($pageid);
      if($page) {
        print '<li>Regenerating '.$page->get_title();
        $page->regenerate();
        print "</li>\n";
        flush();
      }
    }
    print '</ul><p>Done.</p>';
  } else {
    print '<p>There are no pages in the archive to operate on.</p>';
  }
}

$nsisweb->end_page();
?>