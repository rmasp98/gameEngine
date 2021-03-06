/*------------------------------------------------------------------------------
   Copyright (C) 2018 Ross Maspero <rossmaspero@gmail.com>
   All rights reserved.

   This software is licensed as described in the file LICENSE.md, which
   you should have received as part of this distribution.

   Author: Ross Maspero <rossmaspero@gmail.com>
------------------------------------------------------------------------------*/
#include "device_interface/glfw/glfw_interface.h"

#include "utils/logging/log_capture.h"

#include <unistd.h>

namespace quasi_game_engine {

GlfwInterface::GlfwInterface(const char* config_file_name) {
  LOG(INFO, INTERFACE) << "Initialising GLFW";
  if (!glfwInit()) {
    LOG(FATAL, INTERFACE) << "Failed to initialise GLFW";
  }

  // Need to read this in from config file
  // glfwWindowHint(GLFW_SAMPLES, 4); //Antialiasing = 4 samples
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,
                 3);  // Pointing to version of openGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(
      GLFW_OPENGL_PROFILE,
      GLFW_OPENGL_CORE_PROFILE);  // Should find out about other profiles

  // Enable mutlisampling Antialiasing
  // glfwWindowHint(GLFW_SAMPLES, 4);
  // glEnable(GL_MULTISAMPLE);

  CreateWindow("Quasi Game Engine", 1920, 1080, true);
  glfwMakeContextCurrent(window_);

  input_ = std::make_shared<GlfwInput>(window_, config_file_name);
};

void GlfwInterface::CreateWindow(const char* title, int width, int height,
                                 bool full_screen) {
  LOG(INFO, INTERFACE) << "Creating GLFW window";
  if (full_screen) {
    // Gets information about the primary monitor. TODO: is this actually
    // necessary
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window_ = glfwCreateWindow(width, height, title, monitor, nullptr);
  } else {
    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
  }

  // Checks to ensure a window was created properly
  if (window_ == nullptr) {
    LOG(FATAL, INTERFACE) << "Failed to open GLFW window";
  }
}

void GlfwInterface::SwapBuffers() { glfwSwapBuffers(window_); }

void GlfwInterface::PollEvents() { glfwPollEvents(); }

bool GlfwInterface::IsWindowOpen() const {
  // This is tempoary and should be changed later
  return !ActionManager::IsActionActive(ACTION_ESC) &&
         glfwWindowShouldClose(window_) == 0;
}

void GlfwInterface::Update() {
  // May need to update window

  input_->Update();
}

// TODO: This needs to be set at some point
// void SetApiVersion(short major, short minor, bool isCore) {}

}  // namespace quasi_game_engine
