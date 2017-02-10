#include <cmath>

#if defined(_WINDOWS) || defined(__linux__)
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ShaderProgram.h"
#include "Matrix.h"
#include "Texture.h"

#if defined(_WINDOWS) || defined(__linux__)
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

const float HORIZONTAL_VELOCITY = 3.0;
const float HORIZONTAL_DISTANCE = 9.0;
const float BOUNCE_HEIGHT = 1.0;
const float GRAVITY = 9.8;

int main(int argc, char *argv[])
{   
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* displayWindow = SDL_CreateWindow("Bouncing Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
#if defined(_WINDOWS) || defined(__linux__)
    glewInit();
#endif
    
    glViewport(0, 0, 640, 360);
    glClearColor(0.0, 0.75, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ShaderProgram program(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
    Texture ball(RESOURCE_FOLDER"Ball.png");
    Texture ballShadow(RESOURCE_FOLDER"Ball Shadow.png");
    Texture groundShadow(RESOURCE_FOLDER"Ground Shadow.png");
    groundShadow.height = 0.5;
    groundShadow.y = -0.5;
    Matrix projectionMatrix, modelMatrix, viewMatrix;
    projectionMatrix.setOrthoProjection(-3.55, 3.55, -1.0,3.0, -1.0, 1.0);
    glUseProgram(program.programID);
    
    program.setModelMatrix(modelMatrix);
    program.setProjectionMatrix(projectionMatrix);
    program.setViewMatrix(viewMatrix);
        
    SDL_Event event;
    
    bool done = false;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
        }
        const float secondsElapsed = fmod(SDL_GetTicks() / 1000.0f, HORIZONTAL_DISTANCE/HORIZONTAL_VELOCITY);
        const float x = secondsElapsed*HORIZONTAL_VELOCITY-HORIZONTAL_DISTANCE/2;
        const float rotation = -secondsElapsed*HORIZONTAL_VELOCITY*M_PI/2;
        
        const float bouncePeriod = 2*std::sqrt(2*BOUNCE_HEIGHT/GRAVITY);
        const float bounceTime = fmod(secondsElapsed, bouncePeriod) - bouncePeriod/2;
        const float y = BOUNCE_HEIGHT-0.5f*GRAVITY*bounceTime*bounceTime;
        
        glClear(GL_COLOR_BUFFER_BIT);
        modelMatrix.identity();
        
        groundShadow.x = x;
        //modelMatrix.setPosition(x, -0.5, 0);
        //program.setModelMatrix(modelMatrix);
        groundShadow.draw(program);
        
        ball.x = x;
        ball.y = y;
        ball.rotation = rotation;
        //modelMatrix.setPosition(x, y, 0);
        //modelMatrix.setRotation(angle);
        //program.setModelMatrix(modelMatrix);
        ball.draw(program);
        
        ballShadow.x = x;
        ballShadow.y = y;
        //modelMatrix.setRotation(0);
        //program.setModelMatrix(modelMatrix);
        ballShadow.draw(program);
        
        SDL_GL_SwapWindow(displayWindow);
    }
    
    SDL_Quit();
    return 0;
}
