;NSIS Modern User Interface - Language File
;Compatible with Modern UI 1.65

;Language: Estonian (1061)
;By izzo (izzo@hot.ee)

;--------------------------------

  !insertmacro MUI_LANGUAGEFILE_BEGIN "ESTONIAN"

  !define MUI_LANGNAME "Eesti keel" ;Use only ASCII characters (if this is not possible, use the English name)

  !define MUI_TEXT_WELCOME_INFO_TITLE "Tere tulemast $(^Name) paigaldamisele!"
  !define MUI_TEXT_WELCOME_INFO_TEXT "See abiline aitab paigaldada programmi: $(^Name).\r\n\r\nEnne paigaldamise alustamist on soovitatav k�ik teised programmid sulgeda, see v�imaldab teatud s�steemifaile uuendada ilma arvutit taask�ivitamata.\r\n\r\n$_CLICK"
  
  !define MUI_TEXT_LICENSE_TITLE "Litsentsileping"  
  !define MUI_TEXT_LICENSE_SUBTITLE "Enne $(^Name) paigaldamist vaata palun litsentsileping �le."
  !define MUI_INNERTEXT_LICENSE_TOP "Vajuta Page Down, et n�ha �lej��nud teksti."
  !define MUI_INNERTEXT_LICENSE_BOTTOM "Kui sa oled lepingu tingimustega n�us, vali j�tkamiseks 'N�ustun'. $(^Name) paigaldamiseks pead sa tingimustega n�ustuma."
  !define MUI_INNERTEXT_LICENSE_BOTTOM_CHECKBOX "Kui n�ustute lepingu tingimustega, valige allolev m�rkeruut. $(^Name) paigaldamiseks peate lepinguga n�ustuma. $_CLICK"
  !define MUI_INNERTEXT_LICENSE_BOTTOM_RADIOBUTTONS "Kui n�ustute lepingu tingimustega, m�rkige alpool esimene valik. $(^Name) paigaldamiseks peate lepinguga n�ustuma. $_CLICK"

  !define MUI_TEXT_COMPONENTS_TITLE "Vali komponendid"
  !define MUI_TEXT_COMPONENTS_SUBTITLE "Vali millised $(^Name) osad sa soovid paigaldada."
  !define MUI_INNERTEXT_COMPONENTS_DESCRIPTION_TITLE "Kirjeldus"
  !define MUI_INNERTEXT_COMPONENTS_DESCRIPTION_INFO "Nihuta hiir komponendile, et n�ha selle kirjeldust."
  
  !define MUI_TEXT_DIRECTORY_TITLE "Vali asukoht"
  !define MUI_TEXT_DIRECTORY_SUBTITLE "Vali kaust kuhu paigaldada $(^Name)."
  
  !define MUI_TEXT_INSTALLING_TITLE "Paigaldan..."
  !define MUI_TEXT_INSTALLING_SUBTITLE "Palun oota kuni $(^Name) on paigaldatud."
  
  !define MUI_TEXT_FINISH_TITLE "Programm paigaldatud"
  !define MUI_TEXT_FINISH_SUBTITLE "Paigaldus edukalt sooritatud."

  !define MUI_TEXT_ABORT_TITLE "Paigaldus katkestatud"
  !define MUI_TEXT_ABORT_SUBTITLE "Paigaldamine eba�nnestus."

  !define MUI_BUTTONTEXT_FINISH "&L�peta"
  !define MUI_TEXT_FINISH_INFO_TITLE "$(^Name) paigalduse l�pule viimine"
  !define MUI_TEXT_FINISH_INFO_TEXT "$(^Name) on sinu arvutisse paigaldatud.\r\n\r\nAbilise sulgemiseks vajuta L�peta."
  !define MUI_TEXT_FINISH_INFO_REBOOT "$(^Name) paigaldamise l�petamiseks tuleb arvuti taask�ivitada. Kas tahad arvuti kohe taask�ivitada ?"
  !define MUI_TEXT_FINISH_REBOOTNOW "Taask�ivita kohe"
  !define MUI_TEXT_FINISH_REBOOTLATER "Taask�ivitan hiljem k�sitsi"
  !define MUI_TEXT_FINISH_RUN "K�ivita $(^Name)"
  !define MUI_TEXT_FINISH_SHOWREADME "Kuva 'Loe mind'"
  
  !define MUI_TEXT_STARTMENU_TITLE "Vali Start-men�� kaust"
  !define MUI_TEXT_STARTMENU_SUBTITLE "Vali Start-men�� kaust, kust teha otsetee programmi juurde."
  !define MUI_INNERTEXT_STARTMENU_TOP "Vali Start-men�� kaust, kuhu sulle meeldiks paigutada programmi otseteed. V�id ka sisestada nime, et luua uus kaust."
  !define MUI_INNERTEXT_STARTMENU_CHECKBOX "�ra loo otseteid"
  
  !define MUI_TEXT_ABORTWARNING "Oled sa kindel et soovid $(^Name) paigaldamise katkestada?"  
  
  
  !define MUI_UNTEXT_CONFIRM_TITLE "Eemalda $(^Name)"
  !define MUI_UNTEXT_CONFIRM_SUBTITLE "Eemalda $(^Name) oma arvutist."
  
  !define MUI_UNTEXT_UNINSTALLING_TITLE "Eemaldan..."
  !define MUI_UNTEXT_UNINSTALLING_SUBTITLE "Palun oota kuni $(^Name) eemaldatakse."
    
  !define MUI_UNTEXT_FINISH_TITLE "Eemaldamine l�petatud"
  !define MUI_UNTEXT_FINISH_SUBTITLE "Eemaldamine edukalt l�pule viidud."
  
  !define MUI_UNTEXT_ABORT_TITLE "Eemaldamine katkestatud"
  !define MUI_UNTEXT_ABORT_SUBTITLE "Eemaldamine eba�nestus."

!insertmacro MUI_LANGUAGEFILE_END