;NSIS Modern User Interface - Language File
;Compatible with Modern UI 1.68

;Language: Mongolian (1104)
;By Bayarsaikhan Enkhtaivan

;--------------------------------

!insertmacro MUI_LANGUAGEFILE_BEGIN "Mongolian"

  !define MUI_LANGNAME "Mongolian" ;Use only ASCII characters (if this is not possible, use the English name)
  
  !define MUI_TEXT_WELCOME_INFO_TITLE "$(^NameDA) ��������� ������ �����"
  !define MUI_TEXT_WELCOME_INFO_TEXT "$(^NameDA) ��������� �������� �� ���� ������� �����.\r\n\r\n������ ��������� ���� ����� �� ������������ ������ ���� �����. ��������� ��������� ���������� ����������� ����� ��������� ���� ���������.\r\n\r\n$_CLICK"
  
  !define MUI_TEXT_LICENSE_TITLE "��������� �������"  
  !define MUI_TEXT_LICENSE_SUBTITLE "$(^NameDA)-�� ������������ ���� ���������� ��뿿���� ������ ��."
  !define MUI_INNERTEXT_LICENSE_TOP "Page Down ������� ����� ���������� ���� ������� ��."
  !define MUI_INNERTEXT_LICENSE_BOTTOM "����� ���������� ������� ������� ������, Ǻ�����뺺 ������� ����� ������뿿��� ��. $(^NameDA)-�� ��������� ���� ������ ������� ������������."
  !define MUI_INNERTEXT_LICENSE_BOTTOM_CHECKBOX "����� ���������� ������� ������� ������, ������� ������ ����� ������뿿��� ��. $(^NameDA)-�� ��������� ���� ������ ������� ������������. $_CLICK"
  !define MUI_INNERTEXT_LICENSE_BOTTOM_RADIOBUTTONS "����� ���������� ������� ������� ������, �������� ������ �� ������ ������뿿��� ��. $(^NameDA)-�� ��������� ���� ������ ������� ������������. $_CLICK"
  
  !define MUI_TEXT_COMPONENTS_TITLE "�������� ������"
  !define MUI_TEXT_COMPONENTS_SUBTITLE "$(^NameDA)-�� ��������� ���������� ������� ������� ��."
  !define MUI_INNERTEXT_COMPONENTS_DESCRIPTION_TITLE "�������"
  !define MUI_INNERTEXT_COMPONENTS_DESCRIPTION_INFO "�� ����������� �������� ���� ������ ���� ��������� ��������."
  
  !define MUI_TEXT_DIRECTORY_TITLE "������� ��������� ������"
  !define MUI_TEXT_DIRECTORY_SUBTITLE "$(^NameDA) ��������� ������� ����� �����."
  
  !define MUI_TEXT_INSTALLING_TITLE "������� �����"
  !define MUI_TEXT_INSTALLING_SUBTITLE "$(^NameDA)-�� ������� ������� �� ������� ��."
  
  !define MUI_TEXT_FINISH_TITLE "������� �������"
  !define MUI_TEXT_FINISH_SUBTITLE "������� ��������� �����."
  
  !define MUI_TEXT_ABORT_TITLE "�������� ����������"
  !define MUI_TEXT_ABORT_SUBTITLE "�������� �������� �����."
  
  !define MUI_BUTTONTEXT_FINISH "&Һ����"
  !define MUI_TEXT_FINISH_INFO_TITLE "$(^NameDA) ��������� ������� �������"
  !define MUI_TEXT_FINISH_INFO_TEXT "$(^NameDA) �� ���� ���������� ������.\r\n\r\nҺ���� ���� ������ �����."
  !define MUI_TEXT_FINISH_INFO_REBOOT "$(^NameDA)-�� ��������� ��������� �� ����������� ����� ���������� ������. �� ����� ��������� ����� ����� ��?"
  !define MUI_TEXT_FINISH_REBOOTNOW "�.�����"
  !define MUI_TEXT_FINISH_REBOOTLATER "�� ����� �.��������� ����� �����."
  !define MUI_TEXT_FINISH_RUN "$(^NameDA) ����������"
  !define MUI_TEXT_FINISH_SHOWREADME "&Readme ��������"
  
  !define MUI_TEXT_STARTMENU_TITLE "Start ������ ������� �����"
  !define MUI_TEXT_STARTMENU_SUBTITLE "Start ��� ��� $(^NameDA) shortcut-�� ������� �����."
  !define MUI_INNERTEXT_STARTMENU_TOP "Start ������ ��������� shortcut ������ ������� �����. ����� �� ���� ������ ������ �����."
  !define MUI_INNERTEXT_STARTMENU_CHECKBOX "Do not create shortcuts"
  
  !define MUI_TEXT_ABORTWARNING "$(^Name) -�� ���������� ������� ����� ��?"
  
  
  !define MUI_UNTEXT_WELCOME_INFO_TITLE "$(^NameDA) ��������� ������ �������� ������ �����"
  !define MUI_UNTEXT_WELCOME_INFO_TEXT "$(^NameDA) �������� �������� �� ���� ������� �����.\r\n\r\n�������� ���� $(^NameDA) �� ��������� ������� �����.\r\n\r\n$_CLICK"
  
  !define MUI_UNTEXT_CONFIRM_TITLE "$(^NameDA)--�� ������"
  !define MUI_UNTEXT_CONFIRM_SUBTITLE "$(^NameDA) -�� ���� ������������ ���������."
  
  !define MUI_UNTEXT_LICENSE_TITLE "��������� �������"  
  !define MUI_UNTEXT_LICENSE_SUBTITLE "$(^NameDA) �������� ���� ���������� ������� ������ ��."
  !define MUI_UNINNERTEXT_LICENSE_BOTTOM "����� ���������� ������� ������� ������, Ǻ�����뺺 ������� ����� ������뿿��� ��. $(^NameDA)-�� �������� ���� ������ ������� ������������."
  !define MUI_UNINNERTEXT_LICENSE_BOTTOM_CHECKBOX "����� ���������� ������� ������� ������, ������� ������ ����� ������뿿��� ��. $(^NameDA)-�� �������� ���� ������ ������� ������������. $_CLICK"
  !define MUI_UNINNERTEXT_LICENSE_BOTTOM_RADIOBUTTONS "����� ���������� ������� ������� ������, �������� ������ �� ������ ������뿿��� ��. $(^NameDA)-�� �������� ���� ������ ������� ������������. $_CLICK"
  
  !define MUI_UNTEXT_COMPONENTS_TITLE "�������� ������"
  !define MUI_UNTEXT_COMPONENTS_SUBTITLE "$(^NameDA)-�� ������ ������������ �������� ������."
  
  !define MUI_UNTEXT_DIRECTORY_TITLE "�������� ��������� ������"
  !define MUI_UNTEXT_DIRECTORY_SUBTITLE "$(^NameDA)-�� ������ ������� ������."
  
  !define MUI_UNTEXT_UNINSTALLING_TITLE "������ �����"
  !define MUI_UNTEXT_UNINSTALLING_SUBTITLE "$(^NameDA) -�� �������� ������� �� ������� ��."
    
  !define MUI_UNTEXT_FINISH_TITLE "������ �������"
  !define MUI_UNTEXT_FINISH_SUBTITLE "������� ��������� �������."
  
  !define MUI_UNTEXT_ABORT_TITLE "������ ����������"
  !define MUI_UNTEXT_ABORT_SUBTITLE "������� �������� ������."
  
  !define MUI_UNTEXT_FINISH_INFO_TITLE "$(^NameDA) �������� ������� �������"
  !define MUI_UNTEXT_FINISH_INFO_TEXT "$(^NameDA) �� ���� ������������ �������������.\r\n\r\nҺ���� ���� ������ �����."
  !define MUI_UNTEXT_FINISH_INFO_REBOOT "$(^NameDA) �������� ��������� �� ����������� ����� ���������� ������. �� �.��������� ����� ��?"
  
  !define MUI_UNTEXT_ABORTWARNING "$(^Name) ��������� ������� ����� ��?"
  
!insertmacro MUI_LANGUAGEFILE_END