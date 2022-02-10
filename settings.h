#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
    uint filesizeMin;
    uint filesizeMax;

    QStringList includeExtentionsImg; // "jpg", "jpeg", "heic"
    QStringList includeExtentionsVideo; // "mov", "mp4", "mpg", "avi", "mts", "3gp"
    QStringList excludeDirs; // {"Program Files", "Program Files (x86)", "ProgramData", "Windows" };
    QStringList excludeFileWildcard; // *Rip* *WEB* *.TS.* *Dub* *Season* *S??E* *XviD* *Scr* *720i* *720p* *1080i* *1080p

    QSettings* setting;

    void LoadGlobalInclude();
    void LoadIncludeExtentionsImg();
    void LoadIncludeExtentionsVideo();
    void LoadExcludeDirs();
    void LoadExcludeFileWildcard();

    void SaveGlobalInclude();
    void SaveIncludeExtentionsImg();
    void SaveIncludeExtentionsVideo();
    void SaveExcludeDirs();
    void SaveExcludeFileWildcard();

public:
    Settings();

    void load();
    void save();
};

#endif // SETTINGS_H
