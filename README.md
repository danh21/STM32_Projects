# Description
    All projects related to STM32F407 uC, include programming using HAL and register programming.

# Software
    - STM32CubeIDE

# Preferences
    - Set up firmware repo
        + Window -> Preferences 
        + STM32Cube -> Firmware Updater -> Firmware installation repository

# Create project
    - File -> New -> STM32 Project
    - MCU/MPU Selector -> Enter name of MCU to field next to "Commercial Part Number", then choose one of listed MCUs, click Next
    - Enter Project Name, choose Targeted Project Type:
        + STM32Cube: create project using HAL
        + empty: create project using register 
            + Right click to project, choose Properties
            + C/C++ Build -> Settings -> Tool Settings -> MCU GCC Compiler -> Include paths -> Add ..
                "${workspace_loc:/Led_HAL/Drivers/CMSIS/Device/ST/STM32F4xx/Include}"
                "${workspace_loc:/Led_HAL/Drivers/CMSIS/Device/ST/STM32F4xx/Include}"