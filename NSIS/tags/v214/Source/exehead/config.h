#ifndef NSIS_CONFIG_H
#define NSIS_CONFIG_H

#ifndef APSTUDIO_INVOKED // keep msdev's resource editor from mangling the .rc file

#ifndef NSIS_CONFIG_VISIBLE_SUPPORT
  #ifdef NSIS_CONFIG_LICENSEPAGE
    #undef NSIS_CONFIG_LICENSEPAGE
  #endif
  #ifdef NSIS_CONFIG_COMPONENTPAGE
    #undef NSIS_CONFIG_COMPONENTPAGE
  #endif
  #ifdef NSIS_SUPPORT_BGBG
    #undef NSIS_SUPPORT_BGBG
  #endif
  #ifdef NSIS_CONFIG_ENHANCEDUI_SUPPORT
    #undef NSIS_CONFIG_ENHANCEDUI_SUPPORT
  #endif
#endif

#ifdef NSIS_CONFIG_ENHANCEDUI_SUPPORT
  #ifndef NSIS_SUPPORT_HWNDS
    #define NSIS_SUPPORT_HWNDS
  #endif
#endif

#ifdef NSIS_CONFIG_LOG_ODS
  #ifndef NSIS_CONFIG_LOG
    #error NSIS_CONFIG_LOG_ODS relies on NSIS_CONFIG_LOG, but NSIS_CONFIG_LOG is not defined
  #endif
#endif

#if defined(NSIS_CONFIG_CRC_SUPPORT) && defined(NSIS_CONFIG_VISIBLE_SUPPORT)
  #define _NSIS_CONFIG_VERIFYDIALOG
#endif

#if defined(NSIS_CONFIG_UNINSTALL_SUPPORT) && defined(NSIS_CONFIG_VISIBLE_SUPPORT)
  #define _NSIS_CONFIG_UNINSTDLG
#endif

#if defined(NSIS_CONFIG_UNINSTALL_SUPPORT) && defined(NSIS_CONFIG_VISIBLE_SUPPORT)
  #define _NSIS_CONFIG_UNINSTDLG
#endif

#ifdef EXEHEAD
  #ifdef NSIS_CONFIG_COMPRESSION_SUPPORT
    #ifndef NSIS_COMPRESS_USE_ZLIB
      #ifndef NSIS_COMPRESS_USE_BZIP2
        #ifndef NSIS_COMPRESS_USE_LZMA
          #error compression is enabled but zlib, bzip2 and lzma are disabled.
        #endif
      #endif
    #endif
  #endif

  #ifdef NSIS_COMPRESS_USE_ZLIB
    #ifdef NSIS_COMPRESS_USE_BZIP2
      #error both zlib and bzip2 are enabled.
    #endif
    #ifdef NSIS_COMPRESS_USE_LZMA
      #error both zlib and lzma are enabled.
    #endif
  #endif
  #ifdef NSIS_COMPRESS_USE_BZIP2
    #ifdef NSIS_COMPRESS_USE_LZMA
      #error both bzip2 and lzma are enabled.
    #endif
  #endif

  #ifdef NSIS_CONFIG_COMPRESSION_SUPPORT
    #ifdef NSIS_COMPRESS_WHOLE
      #ifdef NSIS_CONFIG_VISIBLE_SUPPORT
        #ifndef _NSIS_CONFIG_VERIFYDIALOG
          #define _NSIS_CONFIG_VERIFYDIALOG
        #endif
      #endif
    #endif
  #endif
#endif // EXEHEAD

#ifdef NSIS_COMPRESS_WHOLE
  #ifndef NSIS_CONFIG_COMPRESSION_SUPPORT
    #error NSIS_COMPRESS_WHOLE defined, NSIS_CONFIG_COMPRESSION_SUPPORT not
  #endif
#endif

#ifdef NSIS_CONFIG_CRC_ANAL
  #ifndef NSIS_CONFIG_CRC_SUPPORT
    #error NSIS_CONFIG_CRC_ANAL defined but NSIS_CONFIG_CRC_SUPPORT not
  #endif
#endif

#ifndef NSIS_COMPRESS_BZIP2_LEVEL
  #define NSIS_COMPRESS_BZIP2_LEVEL 9
#endif

#ifdef NSIS_CONFIG_PLUGIN_SUPPORT
  #ifndef NSIS_SUPPORT_RMDIR
    #error NSIS_CONFIG_PLUGIN_SUPPORT relies on NSIS_SUPPORT_RMDIR, but NSIS_SUPPORT_RMDIR is not defined
  #endif
  #ifndef NSIS_SUPPORT_FILE
    #error NSIS_CONFIG_PLUGIN_SUPPORT relies on NSIS_SUPPORT_FILE, but NSIS_SUPPORT_FILE is not defined
  #endif
  #ifndef NSIS_SUPPORT_ACTIVEXREG
    #error NSIS_CONFIG_PLUGIN_SUPPORT relies on NSIS_SUPPORT_ACTIVEXREG, but NSIS_SUPPORT_ACTIVEXREG is not defined
  #endif
  #ifndef NSIS_SUPPORT_STACK
    #error NSIS_CONFIG_PLUGIN_SUPPORT relies on NSIS_SUPPORT_STACK, but NSIS_SUPPORT_STACK is not defined
  #endif
  #ifndef NSIS_SUPPORT_FNUTIL
    #error NSIS_CONFIG_PLUGIN_SUPPORT relies on NSIS_SUPPORT_FNUTIL, but NSIS_SUPPORT_FNUTIL is not defined
  #endif
  #ifndef NSIS_SUPPORT_DELETE
    #error NSIS_CONFIG_PLUGIN_SUPPORT relies on NSIS_SUPPORT_DELETE, but NSIS_SUPPORT_DELETE is not defined
  #endif
  #ifndef NSIS_SUPPORT_MESSAGEBOX
    #error NSIS_CONFIG_PLUGIN_SUPPORT relies on NSIS_SUPPORT_MESSAGEBOX, but NSIS_SUPPORT_MESSAGEBOX is not defined
  #endif
#endif

#if NSIS_MAX_INST_TYPES > 32
  #error NSIS_MAX_INST_TYPES > 32
#endif

#ifndef NSIS_DEFAULT_LANG
  #define NSIS_DEFAULT_LANG 1033
#endif

typedef char NSIS_STRING[NSIS_MAX_STRLEN];

// I'd love to move this one to config.py, but it must have quotes for #pragma
// and at the same time can't have quotes because the shell will kill it...

#define NSIS_VARS_SECTION ".ndata"

#endif//!APSTUDIO_INVOKED

#endif // NSIS_CONFIG_H
