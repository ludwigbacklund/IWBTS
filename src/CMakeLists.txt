cmake_minimum_required(VERSION 3.3)
project(makefile)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lSDL2 -lSDL2_image")
set(SOURCE_FILES Main.cc Player.cc Sprite.cc Block.cc PlayState.cc StateMachine.cc Projectile.cc Border.cc GameObject.cc Enemy.cc SpeedDemon.cc MenuState.cc MrRabbit.cc MrRabbitProjectile.cc DeathState.cc Checkpoint.cc GrassBlock.cc SpikeBlock.cc TriggerBlock.cc ActiveBlock.h FallBlock.cc JumpBlock.cc Skeletron.cc SkeletronProjectile.cc Continuator.cc FinishBlock.cc Button.cc PlayerProjectile.cc TextureManager.cc)

add_executable(game ${SOURCE_FILES})
