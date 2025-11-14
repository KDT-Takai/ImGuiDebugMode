/// <summary>
/// include Files
/// </summary>
#include "Application.h"   // Application class header
#include <iostream> // Standard I/O
#include <vector>   // Standard vector

int main()
{
    std::unique_ptr<Application> app;       // Application instance
    app = std::make_unique<Application>();  // Create the application
    app->Update();  				        // Run the application main loop
    
    return 0;   // Exit successfully
}