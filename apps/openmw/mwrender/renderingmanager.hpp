#ifndef OPENMW_MWRENDER_RENDERINGMANAGER_H
#define OPENMW_MWRENDER_RENDERINGMANAGER_H

#include <osg/ref_ptr>
#include <osg/Light>

#include "objects.hpp"

#include "renderinginterface.hpp"

namespace osg
{
    class Group;
}

namespace Resource
{
    class ResourceSystem;
}

namespace osgViewer
{
    class Viewer;
}

namespace ESM
{
    struct Cell;
}

namespace MWRender
{

    class StateUpdater;

    class EffectManager;
    class SkyManager;

    class RenderingManager : public MWRender::RenderingInterface
    {
    public:
        RenderingManager(osgViewer::Viewer& viewer, osg::ref_ptr<osg::Group> rootNode, Resource::ResourceSystem* resourceSystem);
        ~RenderingManager();

        MWRender::Objects& getObjects();

        Resource::ResourceSystem* getResourceSystem();

        void setAmbientColour(const osg::Vec4f& colour);

        void setSunDirection(const osg::Vec3f& direction);
        void setSunColour(const osg::Vec4f& colour);

        void configureAmbient(const ESM::Cell* cell);
        void configureFog(const ESM::Cell* cell);
        void configureFog(float fogDepth, const osg::Vec4f& colour);

        void removeCell(const MWWorld::CellStore* store);

        // TODO rename to setRotation/setPosition/setScale, along with the World equivalents
        void rotateObject(const MWWorld::Ptr& ptr, const osg::Quat& rot);
        void moveObject(const MWWorld::Ptr& ptr, const osg::Vec3f& pos);
        void scaleObject(const MWWorld::Ptr& ptr, const osg::Vec3f& scale);

        void setSkyEnabled(bool enabled);

        SkyManager* getSkyManager();

        osg::Vec3f getEyePos();

        void spawnEffect(const std::string &model, const std::string &texture, const osg::Vec3f &worldPosition, float scale = 1.f);

        /// Clear all savegame-specific data
        void clear();

        /// Clear all worldspace-specific data
        void notifyWorldSpaceChanged();

        void update(float dt, bool paused);

        MWRender::Animation* getAnimation(const MWWorld::Ptr& ptr);

    private:
        osgViewer::Viewer& mViewer;
        osg::ref_ptr<osg::Group> mRootNode;
        Resource::ResourceSystem* mResourceSystem;

        osg::ref_ptr<osg::Light> mSunLight;

        std::auto_ptr<Objects> mObjects;
        std::auto_ptr<SkyManager> mSky;
        std::auto_ptr<EffectManager> mEffectManager;

        osg::ref_ptr<StateUpdater> mStateUpdater;

        float mViewDistance;

        void operator = (const RenderingManager&);
        RenderingManager(const RenderingManager&);
    };

}

#endif
