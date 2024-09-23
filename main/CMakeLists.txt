
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

idf_component_register(SRCS "clock_on_screen.cpp" "wifi_setup.c" "sntp_setup.c" "DFRobot_LCD.cpp"
                    INCLUDE_DIRS "."
		    REQUIRES nvs_flash esp_wifi lwip driver)
