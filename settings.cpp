#include <QCoreApplication>
#include <QSettings>

#include "settings.h"

//-----------------------------------------------------------------------------
Settings::Settings()
{
    QString filename = QCoreApplication::applicationDirPath() + "/settings.ini";
    qInfo() << filename;

    setting = new QSettings(filename, QSettings::Format::IniFormat);
}

//-----------------------------------------------------------------------------
void Settings::LoadGlobalInclude()
{
    setting->beginGroup("global-include");
    filesizeMin = setting->value("filesize-min", QVariant(30000)).toUInt(); //30kb
    filesizeMax = setting->value("filesize-max", QVariant(4000000000)).toUInt(); // 4gb
    setting->endGroup();
}

//-----------------------------------------------------------------------------
// Список расширений изображений которой надо сканировать
void Settings::LoadIncludeExtentionsImg()
{
    int size = setting->beginReadArray("include-extentions-img");
    for (int i = 0; i < size; ++i) {
        setting->setArrayIndex(i);
        includeExtentionsImg.append(setting->value("ext").toString());
    }
    setting->endArray();

    // Список по умолчанию
    if(includeExtentionsImg.size() == 0)
        includeExtentionsImg = {"jpg", "jpeg", "heic"};
}


//-----------------------------------------------------------------------------
// Список расширений видео которой надо сканировать
void Settings::LoadIncludeExtentionsVideo()
{
    int size = setting->beginReadArray("include-extentions-video");
    for (int i = 0; i < size; ++i) {
        setting->setArrayIndex(i);
        includeExtentionsVideo.append(setting->value("ext").toString());
    }
    setting->endArray();

    // Список по умолчанию
    if(includeExtentionsVideo.size() == 0)
        includeExtentionsVideo = {"mov", "mp4", "mpg", "avi", "mts", "3gp"};

}

//-----------------------------------------------------------------------------
// Список папок которые не надо сканировать
void Settings::LoadExcludeDirs()
{
    int size = setting->beginReadArray("exclude-dirs");
    for (int i = 0; i < size; ++i) {
        setting->setArrayIndex(i);
        excludeDirs.append(setting->value("dir").toString());
    }
    setting->endArray();

    // Список по умолчанию
    if(excludeDirs.size() == 0)
        excludeDirs = {"Program Files", "Program Files (x86)", "ProgramData", "Windows"};
}

//-----------------------------------------------------------------------------
// Список названий файлов, которые не надо сканировать
void Settings::LoadExcludeFileWildcard()
{
    int size = setting->beginReadArray("exclude-file-wildcard");
    for (int i = 0; i < size; ++i) {
        setting->setArrayIndex(i);
        excludeFileWildcard.append(setting->value("file").toString());
    }
    setting->endArray();

    // Список по умолчанию
    if(excludeFileWildcard.size() == 0)
        excludeFileWildcard = {"*Rip*", "*WEB*", "*.TS.*", "*Dub*", \
                               "*Season*", "*S??E*", "*XviD*", "*Scr*", \
                               "*720i*", "*720p*", "*1080i*", "*1080p*"};
}

//-----------------------------------------------------------------------------
// Загрузка настроек из файла
void Settings::load()
{
    if(!setting)
    {
        qWarning() << "Unable load settings";
        return;
    }

    LoadGlobalInclude();
    LoadIncludeExtentionsImg();
    LoadIncludeExtentionsVideo();
    LoadExcludeDirs();
    LoadExcludeFileWildcard();

    setting->sync();

    foreach(QString group, setting->childGroups())
    {
        setting->beginGroup(group);
        qInfo() << "Group" << group;

        foreach(QString key, setting->childKeys())
            qInfo() << "....key:" << key << "=" << setting->value(key).toString();

        setting->endGroup();
    }

}

//-----------------------------------------------------------------------------
void Settings::SaveGlobalInclude()
{
    setting->beginGroup("global-include");
    setting->setValue("filesize-min", QVariant(filesizeMin));
    setting->setValue("filesize-max", QVariant(filesizeMax));
    setting->endGroup();
}

//-----------------------------------------------------------------------------
void Settings::SaveIncludeExtentionsImg()
{
    setting->beginWriteArray("include-extentions-img");
    for (int i = 0; i < includeExtentionsImg.size(); ++i) {
        setting->setArrayIndex(i);
        setting->setValue("ext", includeExtentionsImg[i]);
    }
    setting->endArray();
}

//-----------------------------------------------------------------------------
void Settings::SaveIncludeExtentionsVideo()
{
    setting->beginWriteArray("include-extentions-video");
    for (int i = 0; i < includeExtentionsVideo.size(); ++i) {
        setting->setArrayIndex(i);
        setting->setValue("ext", includeExtentionsVideo[i]);
    }
    setting->endArray();
}

//-----------------------------------------------------------------------------
void Settings::SaveExcludeDirs()
{
    setting->beginWriteArray("exclude-dirs");
    for (int i = 0; i < excludeDirs.size(); ++i) {
        setting->setArrayIndex(i);
        setting->setValue("dir", excludeDirs[i]);
    }
    setting->endArray();
}

//-----------------------------------------------------------------------------
void Settings::SaveExcludeFileWildcard()
{
    setting->beginWriteArray("exclude-file-wildcard");
    for (int i = 0; i < excludeFileWildcard.size(); ++i) {
        setting->setArrayIndex(i);
        setting->setValue("file", excludeFileWildcard[i]);
    }
    setting->endArray();
}

//-----------------------------------------------------------------------------
// Сохранение настроек в файл
void Settings::save()
{
    SaveGlobalInclude();
    SaveIncludeExtentionsImg();
    SaveIncludeExtentionsVideo();
    SaveExcludeDirs();
    SaveExcludeFileWildcard();
}
