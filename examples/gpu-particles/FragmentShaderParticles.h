
#pragma once

#include "AbstractParticleTechnique.h"


class FragmentShaderParticles : public AbstractParticleTechnique
{
public:
    FragmentShaderParticles(
        const glow::Array<glm::vec4> & postions
    ,   const glow::Array<glm::vec4> & velocities
    ,   const glow::Texture & forces
    ,   const glowutils::Camera & camera);
    virtual ~FragmentShaderParticles();

    virtual void initialize();
    virtual void reset();

    virtual void step(float elapsed);
    virtual void draw(float elapsed);

    virtual void resize();

};