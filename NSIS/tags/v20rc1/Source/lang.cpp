#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "build.h"
#include "DialogTemplate.h"
#include "exehead\resource.h"

extern const char *NSIS_VERSION;

// Default English strings. Should match NSIS_DEFAULT_LANG
// Do not change the first string in every item, it's the LangString
// name for usage in scripts.

typedef enum {
  NONE_STATIC = 0,
  INSTALL_STATIC = 1,
  UNINSTALL_STATIC = 2,
  BOTH_STATIC = 3
} STATICID;

struct {
  char *szLangStringName;
  char *szDefault;
  STATICID eStaticID;
} NLFStrings[NLF_STRINGS] = {
  {"^Branding", "Nullsoft Install System %s", BOTH_STATIC},
  {"^SetupCaption", "$(^Name) Setup", INSTALL_STATIC},
  {"^UninstallCaption", "$(^Name) Uninstall", UNINSTALL_STATIC},
  {"^LicenseSubCaption", ": License Agreement", NONE_STATIC},
  {"^ComponentsSubCaption", ": Installation Options", NONE_STATIC},
  {"^DirSubCaption", ": Installation Folder", NONE_STATIC},
  {"^InstallingSubCaption", ": Installing", NONE_STATIC},
  {"^CompletedSubCaption", ": Completed", NONE_STATIC},
  {"^UnComponentsSubCaption", ": Uninstallation Options", NONE_STATIC},
  {"^UnDirSubCaption", ": Uninstallation Folder", NONE_STATIC},
  {"^ConfirmSubCaption", ": Confirmation", NONE_STATIC},
  {"^UninstallingSubCaption", ": Uninstalling", NONE_STATIC},
  {"^UnCompletedSubCaption", ": Completed", NONE_STATIC},
  {"^BackBtn", "< &Back", NONE_STATIC},
  {"^NextBtn", "&Next >", NONE_STATIC},
  {"^AgreeBtn", "I &Agree", NONE_STATIC},
  {"^AcceptBtn", "I &accept the terms in the License Agreement", NONE_STATIC},
  {"^DontAcceptBtn", "I &do not accept the terms in the License Agreement", NONE_STATIC},
  {"^InstallBtn", "&Install", NONE_STATIC},
  {"^UninstallBtn", "&Uninstall", NONE_STATIC},
  {"^CancelBtn", "Cancel", NONE_STATIC},
  {"^CloseBtn", "&Close", NONE_STATIC},
  {"^BrowseBtn", "B&rowse...", NONE_STATIC},
  {"^ShowDetailsBtn", "Show &details", NONE_STATIC},
  {"^ClickNext", "Click Next to continue.", NONE_STATIC},
  {"^ClickInstall", "Click Install to start the installation.", NONE_STATIC},
  {"^ClickUninstall", "Click Uninstall to start the uninstallation.", NONE_STATIC},
  {"^Name", "Name", BOTH_STATIC},
  {"^NameDA", 0, NONE_STATIC}, // virtual
  {"^Completed", "Completed", NONE_STATIC},
  {"^LicenseText", "Please review the license agreement before installing $(^NameDA). If you accept all terms of the agreement, click I Agree.", NONE_STATIC},
  {"^LicenseTextCB", "Please review the license agreement before installing $(^NameDA). If you accept all terms of the agreement, click the check box below. $_CLICK", NONE_STATIC},
  {"^LicenseTextRB", "Please review the license agreement before installing $(^NameDA). If you accept all terms of the agreement, select the first option below. $_CLICK", NONE_STATIC},
  {"^UnLicenseText", "Please review the license agreement before uninstalling $(^NameDA). If you accept all terms of the agreement, click I Agree.", NONE_STATIC},
  {"^UnLicenseTextCB", "Please review the license agreement before uninstalling $(^NameDA). If you accept all terms of the agreement, click the check box below. $_CLICK", NONE_STATIC},
  {"^UnLicenseTextRB", "Please review the license agreement before uninstalling $(^NameDA). If you accept all terms of the agreement, select the first option below. $_CLICK", NONE_STATIC},
  {"^LicenseData", 0, NONE_STATIC}, // virtual - not processed
  {"^Custom", "Custom", NONE_STATIC},
  {"^ComponentsText", "Check the components you want to install and uncheck the components you don't want to install. $_CLICK", NONE_STATIC},
  {"^ComponentsSubText1", "Select the type of install:", NONE_STATIC},
  {"^ComponentsSubText2_NoInstTypes", "Select components to install:", NONE_STATIC},
  {"^ComponentsSubText2", "Or, select the optional components you wish to install:", NONE_STATIC},
  {"^UnComponentsText", "Check the components you want to uninstall and uncheck the components you don't want to uninstall. $_CLICK", NONE_STATIC},
  {"^UnComponentsSubText1", "Select the type of uninstall:", NONE_STATIC},
  {"^UnComponentsSubText2_NoInstTypes", "Select components to uninstall:", NONE_STATIC},
  {"^UnComponentsSubText2", "Or, select the optional components you wish to uninstall:", NONE_STATIC},
  {"^DirText", "Setup will install $(^NameDA) in the following folder. To install in a different folder, click Browse and select another folder. $_CLICK", NONE_STATIC},
  {"^DirSubText", "Destination Folder", NONE_STATIC},
  {"^DirBrowseText", "Select the folder to install $(^NameDA) in:", NONE_STATIC},
  {"^UnDirText", "Setup will uninstall $(^NameDA) from the following folder. To uninstall from a different folder, click Browse and select another folder. $_CLICK", NONE_STATIC},
  {"^UnDirSubText", "", NONE_STATIC},
  {"^UnDirBrowseText", "Select the folder to uninstall $(^NameDA) from:", NONE_STATIC},
  {"^SpaceAvailable", "Space available: ", BOTH_STATIC},
  {"^SpaceRequired", "Space required: ", BOTH_STATIC},
  {"^UninstallingText", "This wizard will uninstall $(^NameDA) from your computer. $_CLICK", NONE_STATIC},
  {"^UninstallingSubText", "Uninstalling from:", NONE_STATIC},
  {"^FileError", "Error opening file for writing: \r\n\t\"$0\"\r\nHit abort to abort installation,\r\nretry to retry writing the file, or\r\nignore to skip this file", NONE_STATIC},
  {"^FileError_NoIgnore", "Error opening file for writing: \r\n\t\"$0\"\r\nHit retry to retry writing the file, or\r\ncancel to abort installation", NONE_STATIC},
  {"^CantWrite", "Can't write: ", BOTH_STATIC},
  {"^CopyFailed", "Copy failed", BOTH_STATIC},
  {"^CopyTo", "Copy to ", BOTH_STATIC},
  {"^Registering", "Registering: ", NONE_STATIC},
  {"^Unregistering", "Unregistering: ", NONE_STATIC},
  {"^SymbolNotFound", "Could not find symbol: ", BOTH_STATIC},
  {"^CouldNotLoad", "Could not load: ", BOTH_STATIC},
  {"^CreateFolder", "Create folder: ", BOTH_STATIC},
  {"^CreateShortcut", "Create shortcut: ", BOTH_STATIC},
  {"^CreatedUninstaller", "Created uninstaller: ", BOTH_STATIC},
  {"^Delete", "Delete file: ", BOTH_STATIC},
  {"^DeleteOnReboot", "Delete on reboot: ", BOTH_STATIC},
  {"^ErrorCreatingShortcut", "Error creating shortcut: ", BOTH_STATIC},
  {"^ErrorCreating", "Error creating: ", BOTH_STATIC},
  {"^ErrorDecompressing", "Error decompressing data! Corrupted installer?", BOTH_STATIC},
  {"^ErrorRegistering", "Error registering DLL", BOTH_STATIC},
  {"^ExecShell", "ExecShell: ", BOTH_STATIC},
  {"^Exec", "Execute: ", BOTH_STATIC},
  {"^Extract", "Extract: ", BOTH_STATIC},
  {"^ErrorWriting", "Extract: error writing to file ", BOTH_STATIC},
  {"^InvalidOpcode", "Installer corrupted: invalid opcode", BOTH_STATIC},
  {"^NoOLE", "No OLE for: ", BOTH_STATIC},
  {"^OutputFolder", "Output folder: ", BOTH_STATIC},
  {"^RemoveFolder", "Remove folder: ", BOTH_STATIC},
  {"^RenameOnReboot", "Rename on reboot: ", BOTH_STATIC},
  {"^Rename", "Rename: ", BOTH_STATIC},
  {"^Skipped", "Skipped: ", BOTH_STATIC},
  {"^CopyDetails", "Copy Details To Clipboard", BOTH_STATIC},
  {"^LogInstall", "Log install process", BOTH_STATIC},
  {"^Byte", "B", BOTH_STATIC},
  {"^Kilo", "K", BOTH_STATIC},
  {"^Mega", "M", BOTH_STATIC},
  {"^Giga", "G", BOTH_STATIC},
  {"^Font", "MS Shell Dlg", NONE_STATIC},
  {"^FontSize", "8", NONE_STATIC},
  {"^RTL", "0", NONE_STATIC}
};

void CEXEBuild::InitLangTables() {
  keep_ref = false;

  for (int i = 0; i < NLF_STRINGS; i++) {
    NLFRefs[i].iRef = 0;
    NLFRefs[i].iUnRef = 0;

#ifdef NSIS_CONFIG_LOG
    if (i == NLF_NAME) {
      NLFRefs[i].iRef++;
      NLFRefs[i].iUnRef++;
    }
#endif

    if (NLFStrings[i].eStaticID & INSTALL_STATIC) {
      set_uninstall_mode(0);
      DefineLangString(NLFStrings[i].szLangStringName);
    }

#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
    if (NLFStrings[i].eStaticID & UNINSTALL_STATIC) {
      set_uninstall_mode(1);
      DefineLangString(NLFStrings[i].szLangStringName);
    }
#endif
  }

  set_uninstall_mode(0);

  keep_ref = true;
}

LanguageTable* CEXEBuild::GetLangTable(LANGID &lang) {
  int nlt = lang_tables.getlen() / sizeof(LanguageTable);
  LanguageTable *nla = (LanguageTable*)lang_tables.get();

  lang = lang ? lang : last_used_lang;
  last_used_lang = lang;
  LanguageTable *table = 0;

  for (int i = 0; i < nlt; i++) {
    if (lang == nla[i].lang_id) {
      table = &nla[i];
      break;
    }
  }
  if (!table) {
    LanguageTable newtable;

    newtable.lang_id = lang;
    newtable.dlg_offset = 0;
    memset(&newtable.nlf, 0, sizeof(NLF));

    newtable.lang_strings = new StringsArray;

    lang_tables.add(&newtable, sizeof(LanguageTable));
    table = (LanguageTable*)lang_tables.get() + nlt;
  }

  return table;
}

int CEXEBuild::DefineLangString(char *name, int process/*=-1*/) {
  int index, uindex, pos, ret, sn;
  pos = build_langstrings.get(name, &sn, &index, &uindex);
  if (pos < 0) {
    pos = build_langstrings.add(name);
  }

#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
  if (!uninstall_mode) {
#endif
    if (index < 0) {
      index = build_langstring_num++;
    }
    ret = -index - 1;
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
  }
  else {
    if (uindex < 0) {
      uindex = ubuild_langstring_num++;
    }
    ret = -uindex - 1;
  }
#endif

  build_langstrings.set(pos, index, uindex, process);

  // set reference count for NLF strings
  if (keep_ref && name[0] == '^') {
    for (int i = 0; i < NLF_STRINGS; i++) {
      if (!strcmp(name, NLFStrings[i].szLangStringName)) {
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
        if (uninstall_mode)
          NLFRefs[i].iUnRef++;
        else
#endif
          NLFRefs[i].iRef++;

        break;
      }
    }
  }

  return ret;
}

int CEXEBuild::DefineInnerLangString(int id, int process/*=-1*/) {
  bool old_keep_ref = keep_ref;

  // set reference count for NLF strings
  if (keep_ref) {
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
    if (uninstall_mode)
      NLFRefs[id].iUnRef++;
    else
#endif
      NLFRefs[id].iRef++;

    keep_ref = false;
  }

  int ret = DefineLangString(NLFStrings[id].szLangStringName, process);

  keep_ref = old_keep_ref;

  return ret;
}

int CEXEBuild::SetLangString(char *name, LANGID lang, char *string) {
  if (!string || !name) return PS_ERROR;

  LanguageTable *table = GetLangTable(lang);
  if (!table) return PS_ERROR;

  int sn;

  int pos = build_langstrings.get(name, &sn);
  if (pos < 0)
    pos = build_langstrings.add(name, &sn);

  if (table->lang_strings->set(sn, string))
    return PS_WARNING;

  return PS_OK;
}

int CEXEBuild::SetInnerString(int id, char *string) {
  if ((unsigned int)id >= NLF_STRINGS || !string) return PS_ERROR;

  int ret = PS_OK;

  const char *ps = UserInnerStrings.get(id);
  if (ps && *ps)
    ret = PS_WARNING;

  UserInnerStrings.set(id, string);

  return ret;
}

int CEXEBuild::GenerateLangTables() {
  int i;
  LanguageTable *lt = (LanguageTable*)lang_tables.get();

  SCRIPT_MSG("Generating language tables... ");

  // If we have no tables (user didn't set any string and didn't load any NLF) create the default one
  if (!lang_tables.getlen()) {
    LANGID lang = NSIS_DEFAULT_LANG;
    LanguageTable *table = GetLangTable(lang);
    if (!table) return PS_ERROR;

    lt = (LanguageTable*)lang_tables.get();
  }

  // Apply default font
  if (*build_font)
  {
    try {
      init_res_editor();

#define ADD_FONT(id) { \
        BYTE* dlg = res_editor->GetResource(RT_DIALOG, MAKEINTRESOURCE(id), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)); \
        if (dlg) { \
          CDialogTemplate td(dlg); \
          free(dlg); \
          td.SetFont(build_font, build_font_size); \
          DWORD dwSize; \
          dlg = td.Save(dwSize); \
          res_editor->UpdateResource(RT_DIALOG, MAKEINTRESOURCE(id), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), dlg, dwSize); \
          free(dlg); \
        } \
      }

#ifdef NSIS_CONFIG_LICENSEPAGE
      ADD_FONT(IDD_LICENSE);
      ADD_FONT(IDD_LICENSE_FSRB);
      ADD_FONT(IDD_LICENSE_FSCB);
#endif
      ADD_FONT(IDD_DIR);
#ifdef NSIS_CONFIG_COMPONENTPAGE
      ADD_FONT(IDD_SELCOM);
#endif
      ADD_FONT(IDD_INST);
      ADD_FONT(IDD_INSTFILES);
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
      ADD_FONT(IDD_UNINST);
#endif
#ifdef NSIS_CONFIG_CRC_SUPPORT
      ADD_FONT(IDD_VERIFY);
#endif
#undef ADD_FONT
    }
    catch (exception& err) {
      ERROR_MSG("Error while applying font: %s\n", err.what());
      return PS_ERROR;
    }
  }

  // Fill tables with defaults (if needed) and with instruction strings
  // Create language specific resources (currently only dialogs with different fonts)
  int num_lang_tables = lang_tables.getlen() / sizeof(LanguageTable);
  // if there is one string table then there is no need for two sets of dialogs
  int cur_offset = num_lang_tables == 1 ? 0 : 100;
  for (i = 0; i < num_lang_tables; i++)
  {
    if ((lt[i].nlf.m_szFont && !*build_font) || lt[i].nlf.m_bRTL)
    {
      lt[i].dlg_offset = cur_offset;

      char *font = lt[i].nlf.m_szFont;
      if (*build_font) font = 0;

      try {
        init_res_editor();

#define ADD_FONT(id) { \
          BYTE* dlg = res_editor->GetResource(RT_DIALOG, MAKEINTRESOURCE(id), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)); \
          if (dlg) { \
            CDialogTemplate td(dlg,lt[i].nlf.m_uCodePage); \
            free(dlg); \
            if (font) td.SetFont(font, lt[i].nlf.m_iFontSize); \
            if (lt[i].nlf.m_bRTL) td.ConvertToRTL(); \
            DWORD dwSize; \
            dlg = td.Save(dwSize); \
            res_editor->UpdateResource(RT_DIALOG, MAKEINTRESOURCE(id+cur_offset), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), dlg, dwSize); \
            free(dlg); \
          } \
        }

#ifdef NSIS_CONFIG_LICENSEPAGE
        ADD_FONT(IDD_LICENSE);
        ADD_FONT(IDD_LICENSE_FSRB);
        ADD_FONT(IDD_LICENSE_FSCB);
#endif
        ADD_FONT(IDD_DIR);
#ifdef NSIS_CONFIG_COMPONENTPAGE
        ADD_FONT(IDD_SELCOM);
#endif
        ADD_FONT(IDD_INST);
        ADD_FONT(IDD_INSTFILES);
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
        ADD_FONT(IDD_UNINST);
#endif
#ifdef NSIS_CONFIG_CRC_SUPPORT
        ADD_FONT(IDD_VERIFY);
#endif
#undef ADD_FONT
      }
      catch (exception& err) {
        ERROR_MSG("Error while applying NLF font/RTL: %s\n", err.what());
        return PS_ERROR;
      }

      cur_offset += 100;
    }
  }

  // Add language tables into their datablock
  int j, l, cnt, tabsset;
  struct langstring* lang_strings;

  i = num_lang_tables;
  while (i--) {
    build_langtables.add(&lt[i].lang_id, sizeof(LANGID));
    build_langtables.add(&lt[i].dlg_offset, sizeof(int));
    {
      int rtl = lt[i].nlf.m_bRTL ? 1 : 0;
      build_langtables.add(&rtl, sizeof(int));
    }

    int *lst = (int *)((char *)build_langtables.get() + build_langtables.getlen());
    cnt = 0;
    tabsset = 1;

    // write langstrings
    while (tabsset) {
      FillLanguageTable(&lt[i]);

      int lastcnt = cnt;
      cnt = 0;
      tabsset = 0;

      lang_strings = build_langstrings.sort_index(&l);

      for (j = 0; j < l; j++) {
        if (lang_strings[j].index >= 0) {
          if (cnt >= lastcnt || !lst[lang_strings[j].index]) {
            const char *str = lt[i].lang_strings->get(lang_strings[j].sn);
            int tab = 0;

            const char *lsn = build_langstrings.offset2name(lang_strings[j].name);

            if (!str || !*str) {
              if (lsn[0] != '^')
                warning("LangString \"%s\" is not set in language table of language %d", lsn, lt[i].lang_id);
            }
            else {
              char fn[1024];
              sprintf(fn, "LangString %s", lsn);
              curfilename = fn;
              linecnt = lt[i].lang_id;

              tab = add_string(str, lang_strings[j].process, lt[i].nlf.m_uCodePage);
              tabsset++;

              curfilename = 0;
            }

            if (cnt < lastcnt)
              lst[lang_strings[j].index] = tab;
            else
              build_langtables.add(&tab, sizeof(int));
          }

          cnt++;
        }
      }
    }

    // optimize langstrings and check for recursion
    TinyGrowBuf rec;
    for (j = 0; j < build_langstring_num; j++) {
      while (lst[j] < 0) {
        for (int k = 0; (unsigned int)k < rec.getlen() / sizeof(int); k++) {
          if (((int*)rec.get())[k] == lst[j]) {
            const char *name = "(unnamed)";
            for (k = 0; k < l; k++) {
              if (lang_strings[k].index == j) {
                name = build_langstrings.offset2name(lang_strings[k].name);
              }
            }
            ERROR_MSG("Error: LangString %s is recursive!\n", name);
            return PS_ERROR;
          }
        }
        rec.add(&lst[j], sizeof(int));
        lst[j] = lst[-lst[j] - 1];
      }
      rec.resize(0);
    }
  }

  build_header.blocks[NB_LANGTABLES].num = num_lang_tables;
  build_header.langtable_size = build_langtables.getlen() / num_lang_tables;

#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
  set_uninstall_mode(1);

  i = num_lang_tables;
  while (i--) {
    ubuild_langtables.add(&lt[i].lang_id, sizeof(LANGID));
    ubuild_langtables.add(&lt[i].dlg_offset, sizeof(int));
    {
      int rtl = lt[i].nlf.m_bRTL ? 1 : 0;
      ubuild_langtables.add(&rtl, sizeof(int));
    }

    int *lst = (int *)((char *)ubuild_langtables.get() + ubuild_langtables.getlen());
    cnt = 0;
    tabsset = 1;

    // write langstrings
    while (tabsset) {
      FillLanguageTable(&lt[i]);

      int lastcnt = cnt;
      cnt = 0;
      tabsset = 0;

      lang_strings = build_langstrings.sort_uindex(&l);

      for (j = 0; j < l; j++) {
        if (lang_strings[j].uindex >= 0) {
          if (cnt >= lastcnt || !lst[lang_strings[j].uindex]) {
            const char *str = lt[i].lang_strings->get(lang_strings[j].sn);
            int tab = 0;

            const char *lsn = build_langstrings.offset2name(lang_strings[j].name);

            if (!str || !*str) {
              if (lsn[0] != '^')
                warning("LangString \"%s\" is not set in language table of language %d", lsn, lt[i].lang_id);
            }
            else {
              char fn[1024];
              sprintf(fn, "LangString %s", lsn);
              curfilename = fn;
              linecnt = lt[i].lang_id;

              tab = add_string(str, lang_strings[j].process, lt[i].nlf.m_uCodePage);
              tabsset++;

              curfilename = 0;
            }

            if (cnt < lastcnt)
              lst[lang_strings[j].uindex] = tab;
            else
              ubuild_langtables.add(&tab, sizeof(int));
          }

          cnt++;
        }
      }
    }

    // optimize langstrings and check for recursion
    TinyGrowBuf rec;
    for (j = 0; j < ubuild_langstring_num; j++) {
      while (lst[j] < 0) {
        for (int k = 0; (unsigned int)k < rec.getlen() / sizeof(int); k++) {
          if (((int*)rec.get())[k] == lst[j]) {
            const char *name = "(unnamed)";
            for (k = 0; k < l; k++) {
              if (lang_strings[k].uindex == j) {
                name = build_langstrings.offset2name(lang_strings[k].name);
              }
            }
            ERROR_MSG("Error: LangString %s is recursive!\n", name);
            return PS_ERROR;
          }
        }
        rec.add(&lst[j], sizeof(int));
        lst[j] = lst[-lst[j] - 1];
      }
      rec.resize(0);
    }
  }

  build_uninst.blocks[NB_LANGTABLES].num = num_lang_tables;
  build_uninst.langtable_size = ubuild_langtables.getlen() / num_lang_tables;

  set_uninstall_mode(0);
#endif
  
  SCRIPT_MSG("Done!\n");

  return PS_OK;
}

void CEXEBuild::FillLanguageTable(LanguageTable *table) {
  for (int i = 0; i < NLF_STRINGS; i++) {
#ifdef NSIS_CONFIG_UNINSTALL_SUPPORT
    if (!NLFRefs[i].iUnRef && !NLFRefs[i].iRef)
      continue;
#else
    if (!NLFRefs[i].iRef)
      continue;
#endif

    else if (i == NLF_SPACE_REQ || i == NLF_SPACE_AVAIL)
    {
      if (no_space_texts)
      {
        continue;
      }
    }

    int sn, index;
    int pos = build_langstrings.get(NLFStrings[i].szLangStringName, &sn, &index);
    if (pos >= 0) {
      const char *str = table->lang_strings->get(sn);
      if (!str || !*str) {
        const char *us = UserInnerStrings.get(i);
        if (i == NLF_NAME_DA && (!us || !*us))
        {
          // if the user didn't set NLF_NAME_DA we set it to $(^Name)
          table->lang_strings->set(sn, "$(^Name)");
        }
        if (us && *us) {
          table->lang_strings->set(sn, (char *) us);
        }
        else {
          char *dstr = table->nlf.m_szStrings[i] ? table->nlf.m_szStrings[i] : NLFStrings[i].szDefault;
          if (!dstr)
            continue;
          if (i == NLF_BRANDING) {
            char temp[NSIS_MAX_STRLEN + sizeof(NSIS_VERSION)];
            sprintf(temp, dstr, NSIS_VERSION);
            table->lang_strings->set(sn, temp);
            continue;
          }
          else if (i == NLF_FONT)
          {
            char *font = *build_font ? build_font : table->nlf.m_szFont;
            if (font)
              table->lang_strings->set(sn, font);
            else
              table->lang_strings->set(sn, dstr);
            continue;
          }
          else if (i == NLF_FONTSIZE)
          {
            int font_size = *build_font ? build_font_size : table->nlf.m_iFontSize;
            if (font_size)
            {
              char temp[64];
              sprintf(temp, "%d", font_size);
              table->lang_strings->set(sn, temp);
            }
            else
              table->lang_strings->set(sn, dstr);
            continue;
          }
          table->lang_strings->set(sn, dstr);
        }
      }
    }
  }
}

char SkipComments(FILE *f) {
  char c;
  while (c = fgetc(f)) {
    while (c == '\n' || c == '\r') {
      c = fgetc(f); // Skip empty lines
    }
    if (c == '#' || c == ';') {
      while (c = fgetc(f)) {
       if (c == '\n') break;
      }
    }
    else break;
  }
  return c;
}

// NSIS Language File parser
LanguageTable * CEXEBuild::LoadLangFile(char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    ERROR_MSG("Error: Can't open language file!\n");
    return 0;
  }

  // Check header
  char buf[NSIS_MAX_STRLEN];
  buf[0] = SkipComments(f);
  fgets(buf+1, NSIS_MAX_STRLEN, f);

  if (strncmp(buf, "NLF v", 5)) {
    ERROR_MSG("Error: Invalid language file.\n");
    return 0;
  }
  int nlf_version = atoi(buf+5);
  if (nlf_version != NLF_VERSION) {
    if (nlf_version != 2 && nlf_version != 3 && nlf_version != 4 && nlf_version != 5) {
      ERROR_MSG("Error: Language file version doesn't match NSIS version.\n");
      return 0;
    }
  }

  // Get language ID
  buf[0] = SkipComments(f);
  fgets(buf+1, NSIS_MAX_STRLEN, f);
  LANGID lang_id = atoi(buf);

  // Get appropriate table
  LanguageTable *table = GetLangTable(lang_id);
  if (!table)
    return 0;

  NLF *nlf = &table->nlf;

  if (nlf->m_bLoaded) {
    ERROR_MSG("Error: can't load same language file twice.\n");
    return 0;
  }

  // Generate language name
  char *p, *p2, t;

  p = strrchr(filename, '.');
  if (p) {
    t = *p;
    *p = 0;
  }
  p2 = strrchr(filename, '\\');
  if (p2) {
    p2++;
    nlf->m_szName = (char*)malloc(strlen(p2)+1);
    strcpy(nlf->m_szName, p2);
  }
  else {
    nlf->m_szName = (char*)malloc(strlen(filename)+1);
    strcpy(nlf->m_szName, filename);
  }
  if (p) *p = t;

  if (nlf_version != NLF_VERSION) {
    warning_fl("%s language file version doesn't match. Using default English texts for missing strings.", nlf->m_szName);
  }

  int temp;

  // Get font
  buf[0] = SkipComments(f);
  fgets(buf+1, NSIS_MAX_STRLEN, f);
  if (!nlf->m_szFont) {
    temp=strlen(buf);
    while (buf[temp-1] == '\n' || buf[temp-1] == '\r') {
      buf[temp-1] = 0;
      temp--;
    }
    if (buf[0] != '-' || buf[1] != 0) {
      nlf->m_szFont = (char*)malloc(strlen(buf)+1);
      strcpy(nlf->m_szFont, buf);
    }
  }

  buf[0] = SkipComments(f);
  fgets(buf+1, NSIS_MAX_STRLEN, f);
  if (!nlf->m_iFontSize) {
    if (buf[0] != '-' || buf[1] != 0) {
      nlf->m_iFontSize = atoi(buf);
    }
  }

  // Get code page
  nlf->m_uCodePage = CP_ACP;
  buf[0] = SkipComments(f);
  fgets(buf+1, NSIS_MAX_STRLEN, f);
  if (buf[0] != '-' || buf[1] != 0) {
    nlf->m_uCodePage = atoi(buf);
    if (!IsValidCodePage(nlf->m_uCodePage))
      nlf->m_uCodePage = CP_ACP;
  }

  // Get RTL setting
  nlf->m_szStrings[NLF_RTL] = (char *)malloc(2);
  nlf->m_bRTL = false;
  buf[0] = SkipComments(f);
  fgets(buf+1, NSIS_MAX_STRLEN, f);
  if (buf[0] == 'R' && buf[1] == 'T' && buf[2] == 'L' && (!buf[3] || buf[3] == '\r' || buf[3] == '\n')) {
    nlf->m_bRTL = true;
    strcpy(nlf->m_szStrings[NLF_RTL], "1");
  }
  else {
    strcpy(nlf->m_szStrings[NLF_RTL], "0");
  }

  // Read strings
  for (int i = 0; i < NLF_STRINGS - 3 /* ^Font, ^FontSize and ^RTL */; i++) {

    // skip virtual strings
    if (!NLFStrings[i].szDefault)
      continue;
    
    // Fill in for missing strings
    // 0 will mean default will be used from NLFStrings
    switch (i) {
      case NLF_BTN_LICENSE_AGREE:
      case NLF_BTN_LICENSE_DISAGREE:
        if (nlf_version >= 3) break;
      case NLF_LOG_INSTALL_PROCESS:
      case NLF_BYTE:
      case NLF_KILO:
      case NLF_MEGA:
      case NLF_GIGA:
      case NLF_REGISTERING:
      case NLF_UNREGISTERING:
        if (nlf_version >= 4) break;
      case NLF_FILE_ERROR_NOIGNORE:
        if (nlf_version >= 5) break;
      case NLF_USUBCAPTION_OPTIONS:
      case NLF_USUBCAPTION_DIR:
      case NLF_CLICK_NEXT:
      case NLF_CLICK_INSTALL:
      case NLF_CLICK_UNINSTALL:
      case NLF_LICENSE_TEXT:
      case NLF_LICENSE_TEXT_FSCB:
      case NLF_LICENSE_TEXT_FSRB:
      case NLF_ULICENSE_TEXT:
      case NLF_ULICENSE_TEXT_FSCB:
      case NLF_ULICENSE_TEXT_FSRB:
      case NLF_COMP_TEXT:
      case NLF_UCOMP_TEXT:
      case NLF_UCOMP_SUBTEXT1:
      case NLF_UCOMP_SUBTEXT1_NO_INST_TYPES:
      case NLF_UCOMP_SUBTEXT2:
      case NLF_DIR_TEXT:
      case NLF_DIR_BROWSETEXT:
      case NLF_UDIR_TEXT:
      case NLF_UDIR_SUBTEXT:
      case NLF_UDIR_BROWSETEXT:
      case NLF_UNINST_TEXT:
        if (nlf_version >= 6) break;
        nlf->m_szStrings[i] = 0;
        continue;
    }

    buf[0] = SkipComments(f);

    fgets(buf+1, NSIS_MAX_STRLEN, f);
    if (strlen(buf) == NSIS_MAX_STRLEN-1) {
      ERROR_MSG("Error: String too long (string #%d - \"%s\")", i, NLFStrings[i].szLangStringName);
      return 0;
    }
    temp=strlen(buf);

    while (buf[temp-1] == '\n' || buf[temp-1] == '\r') {
      buf[--temp] = 0;
    }

    char *in = buf;

    // trim quotes
    if (buf[0] == '"' && buf[temp-1] == '"') {
      in++;
      buf[--temp] = 0;
    }

    nlf->m_szStrings[i] = (char*)malloc(temp+1);
    for (char *out = nlf->m_szStrings[i]; *in; in++, out++) {
      if (*in == '\\') {
        in++;
        switch (*in) {
          case 'n':
            *out = '\n';
            break;
          case 'r':
            *out = '\r';
            break;
          case 't':
            *out = '\t';
            break;
          default:
            *out++ = '\\';
            *out = *in;
        }
      }
      else *out = *in;
    }
    *out = 0;
  }
  fclose(f);

  nlf->m_bLoaded = true;

  return table;
}

void CEXEBuild::DeleteLangTable(LanguageTable *table) {
  if (table->nlf.m_szName)
    free(table->nlf.m_szName);
  if (table->nlf.m_szFont)
    free(table->nlf.m_szFont);
  delete table->lang_strings;
  for (int i = 0; i < NLF_STRINGS; i++) {
    if (table->nlf.m_szStrings[i])
      free(table->nlf.m_szStrings[i]);
  }
}