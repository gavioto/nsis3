#include "exehead/config.h"
#ifdef NSIS_CONFIG_PLUGIN_SUPPORT

#include "Plugins.h"
#include "Platform.h"
#include "util.h"
#include "dirreader.h"

#ifdef _WIN32
#  include <WinNT.h>
#else
#  include <sys/stat.h>
#endif

extern FILE *g_output;

int PluginsList::add(const char *name, const char *path)
{
  int pos=SortedStringListND<struct plugin>::add(name);
  if (pos == -1) return 1;

  ((struct plugin*)gr.get())[pos].path=strings.add(path, strlen(path)+1);
  ((struct plugin*)gr.get())[pos].dataHandle=-1;
  ((struct plugin*)gr.get())[pos].unDataHandle=-1;

  return 0;
}

char* PluginsList::get(char **name, int *dataHandle/*=0*/, int *uninstDataHandle/*=0*/)
{
  if (dataHandle) *dataHandle=-1;
  if (uninstDataHandle) *uninstDataHandle=-1;
  int v=SortedStringListND<struct plugin>::find(*name);
  if (v==-1) return NULL;
  strcpy(*name, (char*)strings.get()+((struct plugin*)gr.get())[v].name);
  if (dataHandle) *dataHandle=((struct plugin*)gr.get())[v].dataHandle;
  if (uninstDataHandle) *uninstDataHandle=((struct plugin*)gr.get())[v].unDataHandle;
  return (char*)strings.get()+((struct plugin*)gr.get())[v].path;
}

void PluginsList::setDataHandle(const char *name, int dataHandle, int uninstDataHandle)
{
  int v=SortedStringListND<struct plugin>::find(name);
  if (v==-1) return;
  ((struct plugin*)gr.get())[v].dataHandle=dataHandle;
  ((struct plugin*)gr.get())[v].unDataHandle=uninstDataHandle;
}

void Plugins::FindCommands(char* path, bool displayInfo)
{
  if (!path)
    return;

  dir_reader *dr = new_dir_reader();
  dr->read(path);

  dir_reader::iterator files_itr = dr->files().begin();
  dir_reader::iterator files_end = dr->files().end();

  for (; files_itr != files_end; files_itr++) {
    if (!dir_reader::matches(*files_itr, "*.dll"))
      continue;

    string plugin = string(path) + PLATFORM_PATH_SEPARATOR_C + *files_itr;

    GetExports((char *) plugin.c_str(), displayInfo);
  }

  delete dr;
}

void Plugins::GetExports(char* pathToDll, bool displayInfo)
{
  if (pathToDll)
  {
    unsigned char* dlldata    = 0;
    long           dlldatalen = 0;
    bool           loaded     = false;
    char           dllName[1024];
    char           signature[1024];

    dllName[0] = 0;
    char* ptr = strrchr(pathToDll,PLATFORM_PATH_SEPARATOR_C);
    if (ptr && *ptr && *(ptr+1)) strcpy(dllName,ptr+1);

    // find .dll
    int len = strlen(dllName);
    if (len > 4 && !stricmp(dllName + len - 4, ".dll"))
    {
      dllName[len - 4] = 0;
    }

    FILE* dll = fopen(pathToDll,"rb");
    if (dll)
    {
      fseek(dll,0,SEEK_END);
      dlldatalen = ftell(dll);
      fseek(dll,0,SEEK_SET);
      if (dlldatalen > 0)
      {
        dlldata = new unsigned char [dlldatalen];
        if (dlldata)
        {
          size_t bytesread = fread((void*)dlldata,1,dlldatalen,dll);
          if ((long)bytesread == dlldatalen)
            loaded = true;
        }
      }
      fclose(dll);
    }

    if (!loaded)
    {
      if (dlldata) delete[] dlldata;
      return;
    }

    PIMAGE_NT_HEADERS NTHeaders = PIMAGE_NT_HEADERS(dlldata + PIMAGE_DOS_HEADER(dlldata)->e_lfanew);
    if (NTHeaders->Signature == IMAGE_NT_SIGNATURE)
    {
      if (NTHeaders->FileHeader.Characteristics & IMAGE_FILE_DLL)
      {
        if (NTHeaders->OptionalHeader.NumberOfRvaAndSizes <= IMAGE_DIRECTORY_ENTRY_EXPORT) return;

        DWORD ExportDirVA = NTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        DWORD ExportDirSize = NTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
        PIMAGE_SECTION_HEADER sections = IMAGE_FIRST_SECTION(NTHeaders);

        for (int i = 0; i < NTHeaders->FileHeader.NumberOfSections; i++)
          {
          if (sections[i].VirtualAddress <= ExportDirVA
              && sections[i].VirtualAddress+sections[i].Misc.VirtualSize >= ExportDirVA+ExportDirSize)
            {
            PIMAGE_EXPORT_DIRECTORY exports = PIMAGE_EXPORT_DIRECTORY(dlldata + sections[i].PointerToRawData + ExportDirVA - sections[i].VirtualAddress);
            unsigned long *names = (unsigned long*)((unsigned long)exports + (char *)exports->AddressOfNames - ExportDirVA);
            for (unsigned long j = 0; j < exports->NumberOfNames; j++)
            {
              char *name = (char*)exports + names[j] - ExportDirVA;
              wsprintf(signature, "%s::%s", dllName, name);
              m_list.add(signature, pathToDll);
              if (displayInfo)
                fprintf(g_output, " - %s\n", signature);
            }
            break;
          }
        }
      }
    }

    delete[] dlldata;
  }
}

bool Plugins::IsPluginCommand(char* token)
{
  return m_list.get(&token) ? true : false;
}

char* Plugins::GetPluginDll(int uninst, char** command, int* dataHandle)
{  
  *dataHandle = -1;
  
  if (uninst)
    return m_list.get(command, 0, dataHandle);
  else
    return m_list.get(command, dataHandle, 0);
}

void Plugins::SetDllDataHandle(int uninst, char* command, int dataHandle)
{
  if (uninst)
    m_list.setDataHandle(command, -1, dataHandle);
  else
    m_list.setDataHandle(command, dataHandle, -1);
}

#endif
