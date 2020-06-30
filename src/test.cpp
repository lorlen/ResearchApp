#include "db/database.h"
#include "db/user.h"
#include <iostream>
#include <string>

int main()
{
    std::string s = "abcdefghijklmnopqrstuvwxyz"; // ABCDEFGHIJKLMNOPQRSTUVWXYZ
    std::string k = "supertajnykeywhichcanbeundersoodbynarrowamountofrobots";
    Cipher c(s, k);
    if(c.encode("AdmIn") == "AxbIe") std::cout << "cipher test 1 pass" << std::endl; else std::cout << "cipher test 1 fail" << std::endl;
    if(c.decode("AxbIe") == "AdmIn") std::cout << "cipher test 2 pass" << std::endl; else std::cout << "cipher test 2 fail" << std::endl;
    Database db;
    if(db.log_in("admin", "admin42424") == -1) std::cout << "login as admin - wrong password pass" << std::endl; else std::cout << "login as admin  - wrong password fail" << std::endl;
    if(db.log_in("admin", "admin") == 0) std::cout << "login as admin pass" << std::endl; else std::cout << "login as admin fail" << std::endl;
    User* u = db.get_user(0);
    std::cout <<"User operator " << u << std::endl;
    if(db.get_user_name(0) == "admin") std::cout << "user test 1 pass" << std::endl; else std::cout << "user test 1 fail" << std::endl;
    db.change_name("adminchanged");
    if(db.get_user_name(0) == "adminchanged") std::cout << "change name test pass" << std::endl; else std::cout << "change name test fail" << std::endl;
    db.change_login("adminlogin");
    if(u->get_login() == "adminlogin") std::cout << "change login test pass" << std::endl; else std::cout << "change login test fail" << std::endl;
    db.change_login("admin");
    db.add_user("user2", "user2pass", "user2name");
    if(db.add_user("user2", "user2pass", "user2name") == -2) std::cout << "Test inunique adding user pass" << std::endl; else std::cout << "Test inunique adding user fail" << std::endl;
    int res = db.add_admin("user3", "user3pass", "user3name");
    if( res == 2) std::cout << "Test adding admin pass" << std::endl; else std::cout << "Test adding admin fail" << std::endl;
    if(db.remove_user(2) == 0) std::cout<<"Removing user test pass"<<std::endl; else std::cout << "Removing user test fail" << std::endl;
    User* u2 = db.get_user(1);
    if(db.get_user_name(1) == "user2name") std::cout << " getting user name pass" << std::endl; else std::cout << "getting user name fail" << std::endl;
    if(db.change_password("fgaga","fafafaf") == -1) std::cout << "change password unauthorized pass" << std::endl; else std::cout << "change password unauthorized fail" << std::endl;
    if(db.change_password("admin","adminpass") == 0) std::cout << "change password authorized pass" << std::endl; else std::cout << "change password authorized fail" << std::endl;
    db.change_password("adminpass","admin");
    std::cout<<"Removing user::" << std::endl;
    db.add_admin("toRemove", "toRemovepasss", "toRemovename");
    if(db.remove_user(3) == 0) std::cout<<"Removing admin test pass"<<std::endl; else std::cout << "Removing admin test fail" << std::endl;;
    std::cout << ":::::::::::::::::::::::::Sensors tests:::::::::::::::::::::::::::::::" << std::endl;
    int sid2 = db.add_sensor("sensor1","sensor1type","volt");
    if(sid2 == 0)std::cout << "adding sensor 1 test pass" << std::endl; else std::cout << "adding sensor 1 test fail" << std::endl;
    Sensor *se = db.get_sensor(0);
    if(se->get_sensorLabel()=="sensor1")std::cout << "sensor 1 test 1 pass" << std::endl; else std::cout << "sensor 1 test 1 fail" << std::endl;
    if(se->get_sensorType()=="sensor1type")std::cout << "sensor 1 test 2 pass" << std::endl; else std::cout << "sensor 1 test 2 fail" << std::endl;
    if(se->get_sensorUnit()=="volt") std::cout << "sensor 1 test 3 pass" << std::endl; else std::cout << "sensor 1 test 3 fail" << std::endl;
    int sid = db.add_sensor("sensor1toRemove","sensor1typetoremove","volt");
    if(db.delete_sensor(sid) == 0)  std::cout << "removing sensor test  pass" << std::endl; else std::cout << "removing sensor test fail" << std::endl;

    if(db.add_research("Test",Date(2020,5,20),Date(2020,05,31),"ongoing") == 0) std::cout << "adding research test  pass" << std::endl; else std::cout << "adding research test fail" << std::endl;
    db.add_research_point(0, "PointTest", true);
    db.add_research_point(0, "Pointtest2", true);
    if(db.get_research(0)->get_researchPoints().size() == 2) std::cout << "adding research point test  pass" << std::endl; else std::cout << "adding research point test fail" << std::endl;
    db.remove_research_point(0, 1);
    if(db.get_research(0)->get_researchPoints().size() == 1) std::cout << "removing research point test  pass" << std::endl; else std::cout << "removing research point test fail" << std::endl;
    db.add_sensor_research(0, 0, 0);
    db.add_sensor_research(0, 0, "test2", "type2test", "volt");
    db.add_research("Test2",Date(2020,5,20),Date(2020,05,31),"ongoing");
    db.add_research_point(1, "PointTest3", true);
    db.add_research_point(1, "Pointtest5", true);
    db.log_out();
    if(!db.get_currently_loged()) std::cout << "log out test pass" << std::endl; else std::cout << "log out test fail" << std::endl;
}