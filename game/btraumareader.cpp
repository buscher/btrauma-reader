
#include "btraumareader.h"

#include <iostream>

#include <QDir>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDebug>

#include "game/bframe.h"
#include "game/blevel.h"
#include "game/bframeexit.h"
#include "game/bframevideo.h"
#include "game/bframealtmirror.h"
#include "game/bsoundgroup.h"
#include "game/bsoundcomment.h"
#include "bcommentonvisit.h"
#include "bcommentontrigger.h"

#include "platform/bfilemanager.h"

BTraumaReader::BTraumaReader()
{}

BTraumaReader::~BTraumaReader()
{}

BLevel* BTraumaReader::readLevel(const QString& name)
{
    BLevel* level = readFrames(name);
    if (level)
        level = readExits(level);
    if (level)
        level = readMusic(level);
    if (level)
        level = readSoundGroups(level);
    return level;
}

template <class T>
inline static void parseDouble(const QDomNode& node, void (T::*func)(double), T* frame)
{
    bool ok = false;
    double val = node.nodeValue().toDouble(&ok);
    if (ok)
        (frame->*func)(val);
    else
        qDebug() << "failed to double parse:" << node.nodeValue();
}

template <class T>
inline static void parseInt(const QDomNode& node, void (T::*func)(int), T* frame)
{
    bool ok = false;
    double val = node.nodeValue().toInt(&ok);
    if (ok)
        (frame->*func)(val);
    else
        qDebug() << "failed to int parse:" << node.nodeName() << "=" << node.nodeValue();
}

template <class T>
inline static void parseBool(const QDomNode& node, void (T::*func)(bool), T* frame)
{
    if (node.nodeValue().toLower() == QLatin1String("true"))
        (frame->*func)(true);
    else if (node.nodeValue().toLower() == QLatin1String("false"))
        (frame->*func)(false);
    else
        qDebug() << "failed to bool parse:" << node.nodeValue();
}

template <class T>
inline static void parseBoolYesNo(const QDomNode& node, void (T::*func)(bool), T* frame)
{
    if (node.nodeValue().toLower() == QLatin1String("yes"))
        (frame->*func)(true);
    else if (node.nodeValue().toLower() == QLatin1String("no"))
        (frame->*func)(false);
    else
        qDebug() << "failed to boolyesno parse:" << node.nodeValue();
}

BLevel* BTraumaReader::readFrames(const QString& name)
{
    QDomDocument doc(name);
    QString fileName(BFileManager::provideXmlPath(name +  QLatin1String(".xml")));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "unabled to open file" << fileName;
        return 0;
    }
    if (!doc.setContent(&file))
    {
        qDebug() << "failed to set content";
        file.close();
        return 0;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    if (docElem.tagName() != QLatin1String("framecids"))
    {
        qDebug() << "something is wrong, we got:" << docElem.tagName() << " but expected framecids";
        return 0;
    }

    BLevel* level = new BLevel(name);

    for (QDomNode n = docElem.firstChild(); !n.isNull() ; n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if (e.tagName() == QLatin1String("ver"))
        {
            level->setVersion(e.nodeValue().toInt());
        }
        else if (e.tagName() == QLatin1String("framecid"))
        {
            QDomNamedNodeMap map = e.attributes();
            QString frameName;
            if (map.contains(QLatin1String("name")))
                frameName = map.namedItem(QLatin1String("name")).nodeValue();
            else
                qDebug() << "panic! could not find the frame name";
            BFrame *frame = new BFrame(frameName);

            for (int i = 0; i < map.size(); ++i)
            {
                QDomNode nodeItem = map.item(i);

                QString nodeName = nodeItem.nodeName().toLower();
                if (nodeName == QLatin1String("x"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setX, frame);
                }
                else if (nodeName == QLatin1String("y"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setY, frame);
                }
                else if (nodeName == QLatin1String("z"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setZ, frame);
                }
                else if (nodeName == QLatin1String("rx"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setRX, frame);
                }
                else if (nodeName == QLatin1String("ry"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setRY, frame);
                }
                else if (nodeName == QLatin1String("rz"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setRZ, frame);
                }
                else if (nodeName == QLatin1String("scale"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setScale, frame);
                }
                else if (nodeName == QLatin1String("name"))
                    ; //already handled
                else if (nodeName == QLatin1String("priority"))
                {
                    parseInt<BFrame>(nodeItem, &BFrame::setPriority, frame);
                }
                else if (nodeName == QLatin1String("extrabright"))
                {
                    parseBool<BFrame>(nodeItem, &BFrame::setExtraBright, frame);
                }
                else if (nodeName == QLatin1String("nearplane"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setNearPlane, frame);
                }
                else if (nodeName == QLatin1String("antigimblex"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setAntiGimbleX, frame);
                }
                else if (nodeName == QLatin1String("antigimbley"))
                {
                    parseDouble<BFrame>(nodeItem, &BFrame::setAntiGimbleY, frame);
                }
                else
                    qDebug() << '\t' << nodeItem.nodeName() << nodeItem.nodeValue();
            }

            if (e.hasChildNodes())
            {
                 QDomNode videoNode = e.firstChild();
                 QString videoTagName = videoNode.nodeName().toLower();
                 if (videoTagName == QLatin1String("video") && videoNode.hasChildNodes())
                 {
                    QString videoName = videoNode.firstChild().nodeValue();
                    BFrameVideo* video = new BFrameVideo(videoName);
                    QDomNamedNodeMap videoMap = videoNode.attributes();

                    for (int i = 0; i < videoMap.size(); ++i)
                    {
                        QDomNode nodeItem = videoMap.item(i);

                        QString nodeName = nodeItem.nodeName().toLower();
                        if (nodeName == QLatin1String("trigger"))
                        {
                            BFrameExit::ExitType type = BFrameExit::stringToExitType(nodeItem.nodeValue());
                            video->setTriggerType(type);
                        }
                        else if (nodeName == QLatin1String("end"))
                        {
                            BFrameVideo::EndType type = BFrameVideo::stringToEndType(nodeItem.nodeValue());
                            video->setEndType(type);
                        }
                        else if (nodeName == QLatin1String("endflag"))
                        {
                            BFrameVideo::EndFlag flag = BFrameVideo::stringToEndFlag(nodeItem.nodeValue());
                            video->setEndFlag(flag);
                        }
                        else if (nodeName == QLatin1String("vol"))
                        {
                            parseInt<BFrameVideo>(nodeItem, &BFrameVideo::setVolume, video);
                        }
                        else if (nodeName == QLatin1String("zoom"))
                        {
                            parseBool<BFrameVideo>(nodeItem, &BFrameVideo::setZoom, video);
                        }
                        else if (nodeName == QLatin1String("setflag"))
                        {
                            parseInt<BFrameVideo>(nodeItem, &BFrameVideo::setSetFlag, video);
                        }
                        else
                        {
                            qDebug() << "unhandled video attribute" << nodeName;
                        }
                    }
                    frame->setVideo(video);
                 }
                 else if (videoTagName == QLatin1String("altmirror") && videoNode.hasChildNodes())
                 {
                    QString altMirrorName = videoNode.firstChild().nodeValue();
                    BFrameAltMirror* altmirror = new BFrameAltMirror(altMirrorName);
                    QDomNamedNodeMap videoMap = videoNode.attributes();

                    for (int i = 0; i < videoMap.size(); ++i)
                    {
                        QDomNode nodeItem = videoMap.item(i);

                        QString nodeName = nodeItem.nodeName().toLower();
                        if (nodeName == QLatin1String("onflag"))
                        {
                            parseInt<BFrameAltMirror>(nodeItem, &BFrameAltMirror::setOnflag, altmirror);
                        }
                        else
                        {
                            qDebug() << "unhandled altmirror attribute" << nodeName;
                        }
                    }
                    frame->setAltMirror(altmirror);
                 }
                 else
                 {
                     qDebug() << "unhandled sub framecid tag" << videoTagName;
                 }
            }

            level->addFrame(frameName, frame);
        }
    }

    return level;
}

BLevel* BTraumaReader::readExits(BLevel* level)
{
    QDomDocument doc(level->name());
    QString fileName(BFileManager::provideXmlPath(level->configFileName() +  QLatin1String("_exits.xml")));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "unabled to open file" << fileName;
        delete level;
        return 0;
    }
    if (!doc.setContent(&file))
    {
        qDebug() << "failed to set content";
        file.close();
        delete level;
        return 0;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    if (docElem.tagName() != QLatin1String("framecids"))
    {
        qDebug() << "something is wrong, we got:" << docElem.tagName() << " but expected framecids";
        delete level;
        return 0;
    }

    for (QDomNode n = docElem.firstChild(); !n.isNull() ; n = n.nextSibling())
    {
        QDomElement e = n.toElement();
//         qDebug() << e.tagName();

        if (e.tagName() == QLatin1String("ver"))
        {
            ;
//             if (level->version() != e.nodeValue().toInt())
//                 qDebug() << "wrong version:" << level->version() << " != " << e.nodeValue().toInt(); 
        }
        else if (e.tagName() == QLatin1String("framecid"))
        {
            QString frameName;
            QDomNamedNodeMap frameMap = e.attributes();
            if (frameMap.contains(QLatin1String("name")))
                frameName = frameMap.namedItem(QLatin1String("name")).nodeValue();
            else
                qDebug() << "frame does not have a name, panic?";

            BFrame* frame = level->frame(frameName);
            if (!frame)
            {
                qDebug() << frameName;
                qDebug() << "more frame-exits than frame-positions, something is wrong here";
                n = n.nextSibling();
                continue;
            }

            for (QDomNode exitNode = e.firstChild(); !exitNode.isNull() ; exitNode = exitNode.nextSibling())
            {
                QDomElement exitEle = exitNode.toElement();
                QString subTagName = exitEle.tagName().toLower();
//                 qDebug() << '\t' << exitEle.tagName() << exitEle.text();

                if (subTagName == QLatin1String("exit") && exitEle.hasChildNodes())
                {
                    QString exitName = exitEle.firstChild().nodeValue();
//                     qDebug() << "new exit:" << exitName;
                    BFrameExit* exit = new BFrameExit(exitName);

                    QDomNamedNodeMap map = exitNode.attributes();

                    for (int i = 0; i < map.size(); ++i)
                    {
                        QDomNode nodeItem = map.item(i);

                        QString nodeName = nodeItem.nodeName().toLower();
                        if (nodeName == QLatin1String("type"))
                        {
                            BFrameExit::ExitType type = BFrameExit::stringToExitType(nodeItem.nodeValue());
                            exit->setExitType(type);
                        }
                        else if (nodeName == QLatin1String("trigger")) //bool, default false?
                        {
                            parseBool<BFrameExit>(nodeItem, &BFrameExit::setTrigger, exit);
                        }
                        else if (nodeName == QLatin1String("donotforce")) //bool, default false?
                        {
                            parseBool<BFrameExit>(nodeItem, &BFrameExit::setDoNotForce, exit);
                        }
                        else if (nodeName == QLatin1String("onflag")) //int, default 0?
                        {
                            parseInt<BFrameExit>(nodeItem, &BFrameExit::setOnflag, exit);
                        }
                        else if (nodeName == QLatin1String("offflag")) //int, default 0?
                        {
                            parseInt<BFrameExit>(nodeItem, &BFrameExit::setOffflag, exit);
                        }
                        else
                        {
                            qDebug() << exitEle.tagName();
                            qDebug() << "\t" << nodeName;
                        }
                    }

                    if (exit->isVisible())
                        frame->addVisibleExit(exit);
                    else
                        frame->addActionExit(exit);

                }
                else if (subTagName == QLatin1String("polaroid") && exitEle.hasChildNodes()) //int, default -1
                {
                    parseInt<BFrame>(exitNode.firstChild(), &BFrame::setPolaroid, frame);
                }
                else if (subTagName == QLatin1String("deadend") && exitEle.hasChildNodes()) //bool?, string? values: "no"/"yes", default: no
                {
                    parseBoolYesNo<BFrame>(exitNode.firstChild(), &BFrame::setDeadEnd, frame);
                }
                else if (subTagName == QLatin1String("setflag") && exitEle.hasChildNodes()) //int, default 0?
                {
                    parseInt<BFrame>(exitNode.firstChild(), &BFrame::setSetFlag, frame);

                    QDomNamedNodeMap setFlagMap = exitNode.attributes();

                    for (int i = 0; i < setFlagMap.size(); ++i)
                    {
                        QDomNode setFlagNode = setFlagMap.item(i);

                        QString setFlagName = setFlagNode.nodeName().toLower();
                        qDebug() << "unhandled setflag attribute" << setFlagName;
                    }
                }
                else
                {
                    qDebug() << "unhandled tag:" << subTagName;
                }

            }
        }
    }

    return level;
}

BLevel* BTraumaReader::readMusic(BLevel* level)
{
    QDomDocument doc(level->name());
    QString fileName(BFileManager::provideXmlPath(level->configFileName() +  QLatin1String("_music.xml")));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "unabled to open file" << fileName;
        delete level;
        return 0;
    }
    if (!doc.setContent(&file))
    {
        qDebug() << "failed to set content";
        file.close();
        delete level;
        return 0;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    if (docElem.tagName() != QLatin1String("framecids"))
    {
        qDebug() << "something is wrong, we got:" << docElem.tagName() << " but expected framecids";
        delete level;
        return 0;
    }

    for (QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if (e.tagName() == QLatin1String("ver"))
        {
            ;
        }
        else if (e.tagName() == QLatin1String("framecid"))
        {
            QString frameName = e.attributes().namedItem(QLatin1String("name")).nodeValue();
            BFrame* frame = level->frame(frameName);
            if (!frame)
            {
                qDebug() << "could not find frame:" << frameName;
                delete level;
                return 0;
            }

            QDomNode bgsoundNode = e.firstChild();
            QDomElement bgsoundEle = bgsoundNode.toElement();
            if (bgsoundEle.tagName() == QLatin1String("bgsound"))
            {
                QDomNode bgvolNode = bgsoundEle.attributes().namedItem(QLatin1String("volume"));
                parseInt<BFrame>(bgvolNode, &BFrame::setBgVolume, frame);

                frame->setBgSound(bgvolNode.firstChild().nodeValue());
            }
            else
            {
                qDebug() << "unknown sub music tag:" << bgsoundEle.tagName();
            }
        }
        else
        {
            qDebug() << "unknown music tag:" << e.tagName();
        }
    }
    return level;
}

BLevel* BTraumaReader::readSoundGroups(BLevel* level)
{
    QDomDocument doc(level->name());
    QString fileName(BFileManager::provideXmlPath(level->configFileName() +  QLatin1String("_soundgroups.xml")));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "unabled to open file" << fileName;
        delete level;
        return 0;
    }
    if (!doc.setContent(&file))
    {
        qDebug() << "failed to set content";
        file.close();
        delete level;
        return 0;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    if (docElem.tagName() != QLatin1String("soundgroups"))
    {
        qDebug() << "something is wrong, we got:" << docElem.tagName() << " but expected soundgroups";
        delete level;
        return 0;
    }

    for (QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement e = n.toElement();

        if (e.tagName() == QLatin1String("ver"))
        {
            ;
        }
        else if (e.tagName() == QLatin1String("defaultvol") && n.hasChildNodes())
        {
            parseInt<BLevel>(n.firstChild(), &BLevel::setDefaultSoundGroupVolume, level);
        }
        else if (e.tagName() == QLatin1String("soundgroup"))
        {
            QDomNamedNodeMap map = e.attributes();
            QString groupName;
            if (map.contains(QLatin1String("name")))
                groupName = map.namedItem(QLatin1String("name")).nodeValue();
            else
                qDebug() << "soundgroup does NOT have a name";

            BSoundGroup* group = new BSoundGroup(groupName);

            for (QDomNode groupNode = e.firstChild(); !groupNode.isNull(); groupNode = groupNode.nextSibling())
            {
                QDomElement groupEle = groupNode.toElement();
                QString subTagName = groupEle.tagName().toLower();

                if (subTagName == QLatin1String("priority") && groupEle.hasChildNodes())
                {
                    BSoundGroup::SoundPriority sPrio = BSoundGroup::stringToSoundPriority(groupEle.firstChild().nodeValue());
                    group->setSoundPriority(sPrio);
                }
                else if (subTagName == QLatin1String("comment") && groupEle.hasChildNodes())
                {
                    BSoundComment* comment = new BSoundComment();

                    for (QDomNode commentNode = groupEle.firstChild(); !commentNode.isNull(); commentNode = commentNode.nextSibling())
                    {
                        QDomElement commentEle = commentNode.toElement();
                        QString commentSubTagName = commentEle.tagName().toLower();

                        if (commentSubTagName == QLatin1String("sound") && commentEle.hasChildNodes())
                        {
                            comment->setSound(commentEle.firstChild().nodeValue());
                        }
                        else if (commentSubTagName == QLatin1String("subtitle") && commentEle.hasChildNodes())
                        {
                            int langNum = commentEle.attributes().namedItem(QLatin1String("lang")).nodeValue().toInt();
                            QString lang = commentEle.firstChild().nodeValue();
                            comment->addSubtitle(langNum, lang);
                        }
                        else if (commentSubTagName == QLatin1String("subdelay") && commentEle.hasChildNodes())
                        {
                            parseInt<BSoundComment>(commentEle.firstChild(), &BSoundComment::setSubdelay, comment);
                        }
                        else
                        {
                            qDebug() << "unknwon sub-comment-tag" << commentEle.tagName();
                        }
                    }

                    group->addComment(comment);
                }
                else if (subTagName == QLatin1String("ending") && groupEle.hasChildNodes())
                {
                    parseBoolYesNo<BSoundGroup>(groupNode.firstChild(), &BSoundGroup::setEnding, group);
                }
                else
                {
                    qDebug() << "unknown soundgroup-subtag:" << subTagName;
                }
            }

            level->addSoundGroup(groupName, group);
        }
        else
        {
            qDebug() << "unknown soundgroup tag:" << e.tagName();
        }

    }
    return level;
}

BLevel* BTraumaReader::readSounds(BLevel* level)
{
    QDomDocument doc(level->name());
    QString fileName(BFileManager::provideXmlPath(level->configFileName() +  QLatin1String("_sounds.xml")));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "unabled to open file" << fileName;
        delete level;
        return 0;
    }
    if (!doc.setContent(&file))
    {
        qDebug() << "failed to set content";
        file.close();
        delete level;
        return 0;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    if (docElem.tagName() != QLatin1String("framecids"))
    {
        qDebug() << "something is wrong, we got:" << docElem.tagName() << " but expected framecids";
        delete level;
        return 0;
    }

    for (QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if (e.tagName() == QLatin1String("ver"))
        {
            ;
        }
        else if (e.tagName() == QLatin1String("framecid") && e.hasChildNodes())
        {
            QString frameName;
            QDomNamedNodeMap map = e.attributes();
            if (map.contains(QLatin1String("name")))
                frameName = map.namedItem(QLatin1String("name")).nodeValue();
            else
                qDebug() << "PANIC! sounds-frame without name!";

            BFrame* frame = level->frame(frameName);

            for (QDomNode frameCidChild = e.firstChild(); !frameCidChild.isNull(); frameCidChild = frameCidChild.nextSibling())
            {
                QDomElement cidChildEle = frameCidChild.toElement();
                QString tagName = cidChildEle.tagName();
                if (tagName == QLatin1String("commentonvisit") && cidChildEle.hasChildNodes())
                {
                    QString visitName = cidChildEle.firstChild().nodeValue();
                    BCommentOnVisit* visit = new BCommentOnVisit(visitName);

                    QDomNamedNodeMap visitMap = cidChildEle.attributes();

                    for (int i = 0; i < visitMap.size(); ++i)
                    {
                        QDomNode visitItem = visitMap.item(i);

                        QString visitNodeName = visitItem.nodeName().toLower();
                        if (visitNodeName == QLatin1String("markgroupasplayed"))
                        {
                            parseBool<BCommentOnVisit>(visitItem, &BCommentOnVisit::setMarkGroupAsPlayed, visit);
                        }
                        else
                        {
                            qDebug() << "unhandled commentonvisit attribute:" << visitNodeName;
                        }
                    }
                    frame->setCommentOnVisit(visit);
                }
                else if (tagName == QLatin1String("commentontrigger") && cidChildEle.hasChildNodes())
                {
                    QString triggerName = cidChildEle.firstChild().nodeValue();
                    BCommentOnTrigger* trigger = new BCommentOnTrigger(triggerName);

                    QDomNamedNodeMap triggerMap = cidChildEle.attributes();

                    for (int i = 0; i < triggerMap.size(); ++i)
                    {
                        QDomNode visitItem = triggerMap.item(i);

                        QString visitNodeName = visitItem.nodeName().toLower();
                        if (visitNodeName == QLatin1String("showfail"))
                        {
                            parseBool<BCommentOnTrigger>(visitItem, &BCommentOnTrigger::setShowFail, trigger);
                        }
                        else if (visitNodeName == QLatin1String("ignoreplayed"))
                        {
                            parseBool<BCommentOnTrigger>(visitItem, &BCommentOnTrigger::setIgnorePlayed, trigger);
                        }
                        else if (visitNodeName == QLatin1String("gesture"))
                        {
                            BFrameExit::ExitType type = BFrameExit::stringToExitType(visitItem.nodeValue());
                            trigger->setGesture(type);
                        }
                        else
                        {
                            qDebug() << "unhandled commentonvisit attribute:" << visitNodeName;
                        }
                    }
                    frame->addCommentOnTrigger(trigger);
                }
                else
                {
                    qDebug() << "unhandled sounds tag:" << cidChildEle.tagName();
                }
            }
        }
    }
    return level;
}


