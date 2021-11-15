#include "OpenGLContext.h"

#include "ParticleInstancingApp.h"
#include <spdlog/spdlog.h>

int main()
{  
    //auto* app = new ImGuiTestApp();
    //auto* app = new GettingStartedApp();
   // auto* app = new FrameBufferApp();
    //auto* app = new CubeMapApp();
    spdlog::info(__FUNCTION__);

   // auto* app = new PBRTextureApp();
  
   // delete app;*/


  /*  auto* app = new InstancedRenderingApp();
    app->Run();*/

    auto* app = new ParticleInstancingApp();
    while (app->IsRunning())
    {
        app->Update();
    }
    ////auto* app = new Application();
   /* auto* app = new LightingApp();
    app->Run();*/
    delete app;


    return 0;
}
