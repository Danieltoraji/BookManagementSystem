#ifndef PERSONAL_INFO_MENU_H
#define PERSONAL_INFO_MENU_H
#include "../menu_base.h"
#include "services/userservice.h"
#include "model/patron.h"
#include <string>
#include <vector>
#include <iostream>

class PersonalInfoMenu : public MenuBase
{

public:
    void show();
private:
    void displayPersonalInfo();
    void updatePersonalInfo();
    void changePassword();
    void deleteAccount();
};

#endif // PERSONAL_INFO_MENU_H