/*
 * Viewer.h
 *
 *  Created on: 24.03.2014
 *      Author: parojtbe
 */

#pragma once

#include <memory>
#include <string>
#include <stdexcept>
#include <mutex>
#include <map>

#include <OgreAxisAlignedBox.h>
#include <OgreFrameListener.h>

#include <World/Scene.h>

#include <x3ogre_core_export.h>

namespace X3D {

/**
 * Scene Access Interface as mandated by the X3D standard
 * however we only roughly follow the standard here.
 * Correctness is not mandatory.
 * for details see:
 * http://www.web3d.org/documents/specifications/19775-2/V3.3/Part02/servRef.html
 */
class X3OGRECORE_EXPORT SceneAccessInterface : public Ogre::FrameListener  {
    Ogre::SceneNode* _rootNode = nullptr;
    std::string _basePath;

    bool _doDebugDrawing = false;

    // Updates associated by nodeAndField
    std::map<std::pair<std::string,std::string>,std::string> _updates;
    std::mutex _updateMutex;
public:
    SceneAccessInterface(Ogre::SceneNode* rootNode);
    ~SceneAccessInterface();

    void setNodeAttribute(const std::string& nodeName, const std::string& fieldName, const std::string& fieldValue, bool buffer = true);

    std::string getNodeAttribute(const std::string& nodeName, const std::string& fieldName);

    /// adds essential nodes like Viewpoint and Navigation info if not specified in file
    void addEssentialNodes();

    Scene* scene();

    /// listener needed to process buffered attribute events
    bool frameStarted(const Ogre::FrameEvent& evt);

    /**
     * Enables/Disables DebugDrawing
     */
    void switchDebugDrawing();

    /**
	 * length of the world bbox diagonal
	 */
    float getWorldSize();
};

} /* namespace X3D */
