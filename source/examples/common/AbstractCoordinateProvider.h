#pragma once

#include <glbinding/gl/types.h>

#include <glm/glm.hpp>


class Camera;

/** \brief Provides a mapping from screen coordinates to world coordinates.

    This interface is inteded to be used by, e.g., navigation classes that require
    basic scene information based on the pointing devices (mouse, touch, ...) position.

    Note: there are multiple interfaces provided for objAt to allow reduction of 
    depthAt calls and reduction of viewProjection inversion.

    \see WorldInHandNavigation
*/
class AbstractCoordinateProvider
{
public:
    static float depthAt(
        const Camera & camera
    ,   const gl::GLenum depthFormat
    ,   const glm::ivec2 & windowCoordinates);

    static bool validDepth(const float depth);

    static const glm::vec3 unproject(
        const Camera & camera
    ,   const gl::GLenum depthFormat
    ,   const glm::ivec2 & windowCoordinates);

    static const glm::vec3 unproject(
        const Camera & camera
    ,   float depth
    ,   const glm::ivec2 & windowCoordinates);

    static const glm::vec3 unproject(
        const Camera & camera
    ,   const glm::mat4 & viewProjectionInverted
    ,   const float depth
    ,   const glm::ivec2 & windowCoordinates);

public:
    virtual float depthAt(const glm::ivec2 & windowCoordinates) const = 0;

    virtual glm::vec3 objAt(
        const glm::ivec2 & windowCoordinates) const;

    virtual glm::vec3 objAt(
        const glm::ivec2 & windowCoordinates
    ,   const float depth) const = 0;

    virtual glm::vec3 objAt(
        const glm::ivec2 & windowCoordinates
    ,   const float depth
    ,   const glm::mat4 & viewProjectionInverted) const = 0;
};
