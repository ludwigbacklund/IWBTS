CCC=g++
CFLAGS=-std=c++11
SDL= -lSDL2 -lSDL2_image

all: game

game: Main.o StateMachine.o MenuState.o Button.o DeathState.o PlayState.o Sprite.o GameObject.o Checkpoint.o Player.o Border.o Block.o GrassBlock.o ActiveBlock.o TriggerBlock.o SpikeBlock.o FinishBlock.o FallBlock.o JumpBlock.o Continuator.o Enemy.o SpeedDemon.o MrRabbit.o Skeletron.o Projectile.o PlayerProjectile.o MrRabbitProjectile.o SkeletronProjectile.o TextureManager.o
	$(CCC)  Main.o StateMachine.o MenuState.o Button.o DeathState.o PlayState.o Sprite.o GameObject.o Checkpoint.o Player.o Border.o Block.o GrassBlock.o ActiveBlock.o TriggerBlock.o SpikeBlock.o FinishBlock.o FallBlock.o JumpBlock.o Continuator.o Enemy.o SpeedDemon.o MrRabbit.o Skeletron.o Projectile.o PlayerProjectile.o MrRabbitProjectile.o SkeletronProjectile.o TextureManager.o $(SDL) -o game
Main.o: Main.cc
	$(CCC) $(CFLAGS) -c Main.cc

StateMachine.o: StateMachine.cc StateMachine.h
	$(CCC) $(CFLAGS) -c StateMachine.cc

MenuState.o: MenuState.cc MenuState.h
	$(CCC) $(CFLAGS) -c MenuState.cc

Button.o: Button.cc Button.h
	$(CCC) $(CFLAGS) -c Button.cc

DeathState.o: DeathState.cc DeathState.h
	$(CCC) $(CFLAGS) -c DeathState.cc

PlayState.o: PlayState.cc PlayState.h
	$(CCC) $(CFLAGS) -c PlayState.cc

Sprite.o: Sprite.cc Sprite.h
	$(CCC) $(CFLAGS) -c Sprite.cc

GameObject.o: GameObject.cc GameObject.h
	$(CCC) $(CFLAGS) -c GameObject.cc

Checkpoint.o: Checkpoint.cc Checkpoint.h
	$(CCC) $(CFLAGS) -c Checkpoint.cc

Player.o: Player.cc Player.h
	$(CCC) $(CFLAGS) -c Player.cc

Border.o: Border.cc Border.h
	$(CCC) $(CFLAGS) -c Border.cc

Block.o: Block.cc Block.h
	$(CCC) $(CFLAGS) -c Block.cc

GrassBlock.o: GrassBlock.cc GrassBlock.h
	$(CCC) $(CFLAGS) -c GrassBlock.cc

ActiveBlock.o: ActiveBlock.cc ActiveBlock.h
	$(CCC) $(CFLAGS) -c ActiveBlock.cc


TriggerBlock.o: TriggerBlock.cc TriggerBlock.h
	$(CCC) $(CFLAGS) -c TriggerBlock.cc

SpikeBlock.o: SpikeBlock.cc SpikeBlock.h
	$(CCC) $(CFLAGS) -c SpikeBlock.cc

FinishBlock.o: FinishBlock.cc FinishBlock.h
	$(CCC) $(CFLAGS) -c FinishBlock.cc

FallBlock.o: FallBlock.cc FallBlock.h
	$(CCC) $(CFLAGS) -c FallBlock.cc

JumpBlock.o: JumpBlock.cc JumpBlock.h
	$(CCC) $(CFLAGS) -c JumpBlock.cc

Continuator.o: Continuator.cc Continuator.h
	$(CCC) $(CFLAGS) -c Continuator.cc

Enemy.o: Enemy.cc Enemy.h
	$(CCC) $(CFLAGS) -c Enemy.cc

SpeedDemon.o: SpeedDemon.cc SpeedDemon.h
	$(CCC) $(CFLAGS) -c SpeedDemon.cc

MrRabbit.o: MrRabbit.cc MrRabbit.h
	$(CCC) $(CFLAGS) -c MrRabbit.cc

Skeletron.o: Skeletron.cc Skeletron.h
	$(CCC) $(CFLAGS) -c Skeletron.cc

Projectile.o: Projectile.cc Projectile.h
	$(CCC) $(CFLAGS) -c Projectile.cc

PlayerProjectile.o: PlayerProjectile.cc PlayerProjectile.h
	$(CCC) $(CFLAGS) -c PlayerProjectile.cc

MrRabbitProjectile.o: MrRabbitProjectile.cc MrRabbitProjectile.h
	$(CCC) $(CFLAGS) -c MrRabbitProjectile.cc

SkeletronProjectile.o: SkeletronProjectile.cc SkeletronProjectile.h
	$(CCC) $(CFLAGS) -c SkeletronProjectile.cc

TextureManager.o: TextureManager.cc TextureManager.h
	$(CCC) $(CFLAGS) -c TextureManager.cc


run:
	./game

clean:
	rm -rf *.o game

