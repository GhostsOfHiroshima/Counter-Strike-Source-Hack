#include "includes.h"

bool Configuration::Aimbot::aimbotEnabled;
bool Configuration::Aimbot::autoFire;
bool Configuration::Aimbot::silentAim;
bool Configuration::Aimbot::noRecoil;
int Configuration::Aimbot::aimBone;
bool Configuration::Aimbot::autoAim;

bool Configuration::Visuals::Player::Box;
bool Configuration::Visuals::Player::Name;
bool Configuration::Visuals::Player::Health;

float Configuration::Visuals::View::fieldOfView;
bool Configuration::Visuals::Radar::radarEnabled;
float Configuration::Visuals::Radar::radarSize = 100;

bool Configuration::Misc::Movement::autoBunnyhop;
bool Configuration::Misc::Movement::autoStrafe;

bool Configuration::Misc::Spam::locationSpam;
float Configuration::Misc::Spam::locationSpamDelay;
bool Configuration::Misc::Spam::radioSpam;
float Configuration::Misc::Spam::radioSpamDelay;