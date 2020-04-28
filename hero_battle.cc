#include<iostream>

//Base class
class Character
{
public:
  Character(){};
  virtual ~Character(){};

  bool Attack(int ene_consumption, Character *target);
  bool hasNoEnergy(){return Energy>0 ? true : false;};
  bool isDead(){return HP<=0 ? true : false;};

  //setters
  void SetHP(int hp){HP=hp;};
  void SetEnergy(int ene){Energy=ene;};
  void SetHPEnergy(int hp, int ene){HP=hp; Energy=ene;};

  //getters
  int GetHP    (void){return HP;};
  int GetEnergy(void){return Energy;}

protected:
  int HP;
  int Energy;
};

bool Character::Attack(int ene_consumption, Character *target){
  //This method consume given energy, and decrease HP of target by that amount.
  bool success = true;
  if(this->Energy >= ene_consumption){
    Energy-=ene_consumption;
    int target_hp = target->GetHP();
    target->SetHP(target_hp-ene_consumption);
  }else{
    success = false;
  }
  return success;
};


//Derived classes
class Hero: public Character
{
public:
  Hero(){};
  Hero(int hp, int ene){HP=hp; Energy=ene;};
  virtual ~Hero(){};

private:
};

class Bakemono: public Character
{
public:
  Bakemono(){};
  Bakemono(int hp, int ene){HP=hp; Energy=ene;};
  virtual ~Bakemono(){};

private:
};


//Main
int main(void){

  //Instantiate heros
  Hero* hero_a = new Hero();
  hero_a->SetHP(10);
  hero_a->SetEnergy(10);
  std::cout<<hero_a->GetHP()<<", "<<hero_a->GetEnergy()<<std::endl;

  int hero_init_hp = 20;
  int hero_init_ene = 20;
  Hero* hero_b = new Hero(hero_init_hp,hero_init_ene);
  std::cout<<hero_b->GetHP()<<", "<<hero_b->GetEnergy()<<std::endl;

  //Instantiate opponent
  Bakemono* bakemono = new Bakemono(1000,2000);
  std::cout<<bakemono->GetHP()<<", "<<bakemono->GetEnergy()<<std::endl;

  std::cout<<std::endl;

  int turn = 0;
  bool heroLose = false;
  while(1){
    std::cout<<"-----------------------------"<<std::endl;
    std::cout<<"Turn: "<<turn<<std::endl;
    //Hero's turn
    hero_a->Attack(2,bakemono);
    hero_b->Attack(2,bakemono);

    std::cout<<"Hero->Bakemono"<<std::endl;
    std::cout<<"  Hero(A): HP="<<hero_a->GetHP()<<", Energy="<<hero_a->GetEnergy()<<std::endl;
    std::cout<<"  Hero(B): HP="<<hero_b->GetHP()<<", Energy="<<hero_b->GetEnergy()<<std::endl;
    std::cout<<"  Bakemono: HP="<<bakemono->GetHP()<<", Energy="<<bakemono->GetEnergy()<<std::endl;

    if(bakemono->isDead()) break;

    //Bakemono's turn
    bakemono->Attack(2,hero_a);
    bakemono->Attack(2,hero_b);

    std::cout<<"Bakemono->Hero"<<std::endl;
    std::cout<<"  Hero(A): HP="<<hero_a->GetHP()<<", Energy="<<hero_a->GetEnergy()<<std::endl;
    std::cout<<"  Hero(B): HP="<<hero_b->GetHP()<<", Energy="<<hero_b->GetEnergy()<<std::endl;
    std::cout<<"  Bakemono: HP="<<bakemono->GetHP()<<", Energy="<<bakemono->GetEnergy()<<std::endl;

    if(hero_a->isDead() && hero_a->isDead()){
      heroLose = true;
      break;
    }

    turn++;
  }

  std::cout<<"=============================="<<std::endl;
  if(heroLose){
    std::cout<<"Heros are defeated..."<<std::endl;
  }else{
    std::cout<<"Heros win!!"<<std::endl;
  }
  std::cout<<"=============================="<<std::endl;

  return 0;
}
