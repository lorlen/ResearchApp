#include "db/database.h"

Database::Database(/* args */): cipher(alphabet, key)
{
    User *u = new User("admin", sha256("admin"), "admin", 0, true);
    users.insert(std::pair<uint, User*>(0, u));
    next_user_id = 1;

    std::ifstream infofile("settings.json");
    if(infofile.good())
    {
        // loading setting and informaton from main file 
        json data;
        infofile >> data;
        ufilename = data["users"];
        rfilename = data["research"]; 
        sfilename = data["sensors"];
        //User::nextid = data["usernextid"];
        next_user_id = data["usernextid"];
        next_research_id = data["researchnextid"];
        next_sensor_id = data["sensornextid"];
        next_research_point_id = data["pointnextid"];
        users_amount = data["usersAmount"];
        research_amount = data["researchAmount"];
        sensors_amount = data["sensorsAmount"];
        reserach_point_amount = data["researchPointAmount"];
        std::ifstream ufile(ufilename);
        if(ufile.good()) // loading users
        {
            ufile >> users_json;
            load_users(users_json);
        }
        else throw DatabaseReadProblem(ufilename);
        ufile.close();
        std::ifstream rfile(rfilename);
        if(rfile.good()) // loading research and reserch points
        {
            rfile >> research_json;
            load_researchs(research_json);
        }
        else throw DatabaseReadProblem(rfilename);
        rfile.close(); 
        std::ifstream sfile(sfilename);
        if(sfile.good()) // loading sensors
        {
            sfile >> sensors_json;
            load_sensors(sensors_json);
        }
        else throw DatabaseReadProblem(sfilename);
        sfile.close();         
    }
    else
    {
        first_run(); 
    }
    

}

void Database::first_run()
{
        json data;
        std::ofstream ifile("settings.json");
        data["users"] = "users.json";
        data["research"] = "research.json";
        data["sensors"] = "sensors.json";
        data["usernextid"] = 1;
        data["researchnextid"] = 0;
        data["sensornextid"] = 0;
        data["pointnextid"] = 0;
        data["usersAmount"] = 1;
        data["researchAmount"] = 0;
        data["sensorsAmount"] = 0;
        data["researchPointAmount"] = 0;
        data >> ifile;
        ifile.close();
        data.clear();
        std::ofstream uf("users.json");
        uint i = 0;
        json d;
        save_user(i);
        users_json>>uf;
        uf.close();
        std::ofstream rf("research.json");
        d["-1"] = "Files contains filesnames of other files";
        d >> rf;
        rf.close();
        d.clear();
        std::ofstream sf("sensors.json");
        d["-1"] = "Files contains sensors";
        d >> sf;
        sf.close();
}

Database::~Database()
{
    shutdown();

    for(auto j: research_jsons) delete j;
    for(auto& u:users) delete u.second;
    for(auto& r:researchs) delete r.second;
    for(auto& s:sensors) delete s.second;
}

void Database::shutdown()
{
    json data;
    data["users"] = ufilename;
    data["research"] = rfilename;
    data["sensors"] = sfilename;
    data["usernextid"] = next_user_id;
    data["researchnextid"] = next_research_id;
    data["sensornextid"] = next_sensor_id;
    data["pointnextid"] = next_research_point_id;
    data["usersAmount"] = users_amount;
    data["researchAmount"] = research_amount;
    data["sensorsAmount"] = sensors_amount;
    data["researchPointAmount"] = reserach_point_amount;
    std::ofstream ifile("settings.json");
    data >> ifile;
    ifile.close();
    save_users();
    save_researchs();
    save_sensors();
}

int Database::add_user(std::string login, std::string password, std::string name)
{
    return add_u_inner(login, password, name, false);
}

int Database::add_admin(std::string login, std::string password, std::string name)
{
    return add_u_inner(login, password, name, true);
}

int Database::add_u_inner(std::string login, std::string password, std::string name, bool level)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            if(logins.insert(login).second)
            {
            std::string hash_pass = sha256(password);
            User* u = new User(login, hash_pass, name, next_user_id, level);
            next_user_id++;
            users.insert(std::pair<uint, User*>(u->get_id(),u));
            #ifdef _Debug
            std::cout << "Adding user: " << login << "next id " <<next_user_id <<"User id"<< u->get_id() << std::endl;
            #endif
            return u->get_id();
            }
            else{
            #ifdef _Debug
            std::cout << "Can't add user, not unique login" << std::endl;
            #endif
            return -2;
            }
        }
        else 
        {
            #ifdef _Debug
            std::cout << "Can't add user, not an admin" << std::endl;
            #endif
            return -1;
        }
    }
    else{
        #ifdef _Debug
        std::cout << "Not logged in" << std::endl;
        #endif
        return -44;
    } 
}


int Database::log_in(std::string login, std::string password)
{
    std::string hash_pass = sha256(password);
    for(auto& element: users)
    {
        if(element.second->get_login()==login && element.second->check_password(hash_pass))
        {
            currently_logged = element.second;
            #ifdef _Debug
            std::cout << "loging user : " << login << " pass: "<< password << " id: "<< element.first << std::endl;
            #endif
            return element.first;
        }
    }
    #ifdef _Debug
    std::cout << "unsuccesful login attempt user : " << login << " pass: "<< password << std::endl;
    #endif
    return -5;
}

void Database::save_user(uint id)
{
    User* u = users.find(id)->second;
    save_user(u);
}

void Database::save_user(User* u)
{
    std::string credentials = cipher.encode(u->get_credenital_string());
    json data;
    data["user"] = credentials;
    json info;
    info["name"] = cipher.encode(u->get_name());
    info["attached"] = u->get_attached();
    info["author"] = u->get_authored();
    info["level"] = u->is_admin();
    data["info"] = info;
    users_json[std::to_string(u->get_id())] = data;
    #ifdef _Debug
        std::cout << "Saving user: " << u->get_credenital_string() << " info " << u->get_name() << std::endl;
    #endif
}

void Database::save_users()
{
    users_json.clear();
    for(auto& element: users)
    {
        save_user(element.second);
    }
    std::ofstream of("users.json");
    users_json >> of;
}


int Database::modify_user(uint id, User* u)
{
    if(currently_logged->is_admin())
        {
            if(users.find(id)->second->get_login() != u->get_login())
            {
                if(logins.insert(u->get_login()).second)
                {
                    users.find(id)->second->operator=(u);
                    return 0;
                }
                else return -2;
            }
            else
            {
                users.find(id)->second->operator=(u);
                return 0;
            }
            
            
        }
    else return -1;
}


int Database::modify_user_login(uint id, std::string new_login) 
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            users.find(id)->second->change_login(new_login);
            return 0;
        }return -1;
    }return -44;
}


int Database::modify_user_name(uint id, std::string new_name) 
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            users.find(id)->second->change_name(new_name);
            return 0;
        }return -1;
    }return -44;
}


int Database::modify_user_password(uint id, std::string old_pasword, std::string new_password) 
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            std::string oldpass = sha256(old_pasword);
            std::string newpass = sha256(new_password);
            return users.find(id)->second->change_password(oldpass, newpass);
        }return -1;
    }return -44;
}

void Database::load_users(json& data)
{
    for(auto& us: data.items())
    {
        if(us.key() == "0") continue; // don't load admin from file  
        User* uprt;
        json udata = us.value();
        std::string pureinfo = udata["user"];
        std::string credentials = cipher.decode(pureinfo);
        std::vector<std::string> *cred = split(credentials, ':');
        std::string logggin = cred->operator[](0);
        logins.insert(logggin);
        std::string pass = cred->operator[](1);
        uprt = new User(cred->operator[](0), cred->operator[](1), cipher.decode(udata["info"]["name"]),std::stoi(us.key()), udata["info"]["level"].get<bool>());
        uprt->set_attached(udata["info"]["attached"].get<std::vector<uint>>());
        uprt->set_authored(udata["info"]["author"].get<std::vector<uint>>());
        users.insert(std::pair<uint, User*>(std::stoi(us.key()),uprt));
    #ifdef _Debug
        std::cout << "Pure info: " << pureinfo << " after deconding: " << credentials << std::endl <<" login: "<< logggin << " pass: "<< pass << std::endl;
        std::cout << "Loading user: " << uprt->get_credenital_string() << " info " << uprt->get_name() << std::endl;
    #endif
    }
}

void Database::load_researchs(json& data)
{
    std::vector<ResearchPoint*> points;
    json rdata;
    std::ifstream irfile;
    for(auto& file:data.items())
    {
        if(file.key() == "-1") continue;
        Research *r = new Research();
        irfile.open(file.value());
        irfile >> rdata;
        r->change_researchTitle(rdata["title"]);
        r->set_state(rdata["state"]);//
        r->set_research_ID(rdata["id"]);
        r->set_author(rdata["author"]);
        r->set_s_date(Date(rdata["s_date"]["year"],rdata["s_date"]["month"], rdata["s_date"]["day"]));
        r->set_d_date(Date(rdata["d_date"]["year"],rdata["d_date"]["month"], rdata["d_date"]["day"]));
        r->set_users(rdata["users"].get<std::vector<uint>>()); //change form users id to user objectc ??
        // for(auto us: uvec)
        // {
        //     r->add_user(us);
        // }
        json rrpoints = rdata["reseachPoints"];
        points.clear();
        for(auto& point: rrpoints.items())
        {
            ResearchPoint* p = new ResearchPoint;
            p->set_researchPoint_ID(point.value()["id"]);
            p->change_researchPointTitle(point.value()["title"]);
            p->set_required(point.value()["required"].get<bool>());
            p->set_sensors(point.value()["sensor"].get<std::vector<uint>>());
            p->set_checked(point.value()["checked"].get<bool>());
            p->set_order(point.value()["order"]);
            points.push_back(p);
        };
        std::sort(points.begin(), points.end());
        r->set_researchPoints(points);

        #ifdef _Debug
        std::cout << "loading research: " << r->get_researchTitle() << " id: "<<  r -> get_research_ID()<< std::endl;
        #endif
        researchs.insert(std::pair<uint, Research*>(r->get_research_ID(),r));
        rdata.clear();
        irfile.close();

    }

}


uint Database::get_next_point_id() 
{
    uint to_r = next_research_point_id;
    next_research_point_id++;
    return to_r; 
}

void Database::save_researchs()
{
    std::ofstream orfile;
    json research;
    json date;
    json point;
    json points;
    research_json.clear();
    research_json["-1"] = "This file contains filenames of other files";
    for(auto& r: researchs)
    {
        research["title"] = r.second->get_researchTitle(); 
        research["state"] = r.second -> get_state();
        research["id"] = r.second -> get_research_ID();
        research["author"] = r.second -> get_author_user();
        research["users"] = r.second->get_users_ID();
        date["year"] = r.second->get_start_date().year();
        date["month"] = r.second ->get_start_date().month();
        date["day"] = r.second->get_start_date().day();
        research["s_date"] = date;
        date.clear();
        date["year"] = r.second->get_deadline_date().year();
        date["month"] = r.second ->get_deadline_date().month();
        date["day"] = r.second->get_deadline_date().day();
        research["d_date"] = date;
        date.clear();
        points.clear();
        sort_research_points(r.second->get_research_ID());
        for(auto p: r.second->get_researchPoints())
        {
            point.clear();
            point["id"] = p->get_researchPoint_ID();
            point["title"] = p->get_researchPointTitle();
            point["required"] = p->is_requiredMeasurement();
            point["sensor"] = p->get_sensors();
            point["checked"] = p->is_checked();
            point["order"] = p->get_order();
            points[std::to_string(p->get_researchPoint_ID())] = point;
        }
        research["reseachPoints"] = points;
        std::string fn = "reseach_" + std::to_string(r.second->get_research_ID()) + ".json";
        orfile.open(fn);
        research >> orfile;
        research.clear();
        orfile.close();
        research_json[std::to_string(r.second->get_research_ID())] = fn;
        #ifdef _Debug
        std::cout << "saving research: " << r.second->get_researchTitle() << " id: "<<  r.second -> get_research_ID()<< std::endl;
        #endif
    }
    orfile.open("research.json");
    research_json >> orfile;
    orfile.close();
}

void Database::load_sensors(json data)
{
    //json s = data["sensors"];
    json sensor;
    for(auto &element : data.items())
    {
        if(element.key() == "-1") continue;
        sensor.clear();
        sensor = element.value();
        Sensor* sptr = new Sensor();
        sptr->change_sensorType(sensor["type"]);
        sptr->change_sensorLabel(sensor["lable"]);
        sptr->change_sensorUnit(sensor["unit"]);
        sptr->set_sensor_ID(sensor["id"]);
        sensors.insert(std::pair<uint, Sensor*>(std::stoi(element.key()), sptr));
        #ifdef _Debug
        std::cout << "Loading sensor: " << sptr->get_sensorLabel() << " type " << sptr->get_sensorType()<< " id: "<<  sptr->get_sensor_ID()<< std::endl;
        #endif
    }
}


void Database::sort_research_points(uint id) 
{
    std::vector<ResearchPoint*> vec = researchs.find(id)->second->get_researchPoints();
    std::sort(vec.begin(), vec.end(), [](ResearchPoint* a, ResearchPoint* b) { return (*a < *b); });
    researchs.find(id)->second->set_researchPoints(vec);
}

void Database::save_sensors()
{
    sensors_json.clear();
    json sensor;
    sensors_json["-1"] = "This files contains sensors";
    for(auto& element: sensors)
    {
        sensor.clear();
        sensor["lable"] = element.second->get_sensorLabel();
        sensor["type"] = element.second->get_sensorType();
        sensor["unit"] = element.second->get_sensorUnit();
        sensor["id"] = element.second->get_sensor_ID();
        sensors_json[std::to_string(element.second->get_sensor_ID())] = sensor;
        #ifdef _Debug
        std::cout << "saving sensor: " << element.second->get_sensorLabel() << " type " << element.second->get_sensorType()<< " id: "<<  element.second->get_sensor_ID()<< std::endl;
        #endif
    }
    std::ofstream sf("sensors.json");
    sensors_json >> sf;
    sf.close();
}

std::vector<std::string>* Database::split(std::string text, char sppliter = ':')
{
    std::vector<std::string> *vec = new std::vector<std::string>;
    std::string buf1 = text.substr(0, text.find(sppliter));
    std::string buf2 = text.substr(text.find(sppliter)+1, text.size());
    vec->push_back(buf1);
    vec->push_back(buf2);
    return vec;
}


int Database::add_research(Research* r)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            r->set_research_ID(next_research_id);
            researchs.insert(std::pair<uint, Research*>(next_research_id, r));
            next_research_id++;
            return next_research_id -1 ;
        }
        return -1;
    } return -44;
}

int Database::add_research(std::string title, Date s_d, Date d_d, std::string st, uint author_id)
{
    Research *rptr = new Research(title, s_d, d_d, st, author_id, next_research_id);
    return add_research(rptr);
}

int Database::add_research(std::string title, Date s_d, Date d_d, std::string st)
{
    Research *rptr = new Research(title, s_d, d_d, st, currently_logged->get_id(), next_research_id);
    return add_research(rptr);
}

int Database::remove_research(uint id)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            delete researchs.find(id)->second;
            researchs.erase(id);
            return 0;
        }
        return - 1;
    } return -44;
}

int Database::log_out()
{
    currently_logged = nullptr;
    return 0;
}


int Database::add_sensor(std::string lable, std::string type, std::string unit)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            #ifdef _Debug
            std::cout << "Adding sensor"<< std::endl;
            #endif
            Sensor *sptr = new Sensor(lable, type, unit, next_sensor_id);
            sensors.insert(std::pair<uint, Sensor*>(next_sensor_id, sptr));
            ++next_sensor_id;
            return next_sensor_id-1;
        }
        else return -1;
    } return -44;
}

int Database::delete_sensor(uint id)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            #ifdef _Debug
            std::cout << "Deleting sensor"<< std::endl;
            #endif
            delete sensors.find(id)->second;
            sensors.erase(id);
            return 0;
        }
        return -1;
    } return -44;
}


int Database::modify_sensor_lable(uint id, std::string lable) 
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            sensors.find(id)->second->change_sensorLabel(lable);
            return 0;
        }
        return -1;
    } return -44;
}

int Database::modify_sensor_type(uint id, std::string type) 
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            sensors.find(id)->second->change_sensorType(type);
            return 0;
        }
        return -1;
    } return -44;
}

int Database::modify_sensor_unit(uint id, std::string unit) 
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            sensors.find(id)->second->change_sensorUnit(unit);
            return 0;
        }
        return -1;
    } return -44;
}

int Database::change_password(std::string old_passwword, std::string new_password)
{
    if(currently_logged)
    {
        new_password = sha256(new_password);
        old_passwword = sha256(old_passwword);
        return currently_logged->change_password(old_passwword, new_password);
    }return -44;
}

void Database::change_login(std::string new_login)
{
    if(currently_logged)
    {
        //if(logins.insert(new_login).second)
        //{
            currently_logged->change_login(new_login);
        //}
    }
}

void Database::change_name(std::string new_name)
{
    if(currently_logged)
    {
        currently_logged->change_name(new_name);
    }
}

bool Database::is_admin()
{
    if(currently_logged)
    {
        return currently_logged->is_admin();
    } return false;
}

bool Database::is_admin(uint id)
{
    return users.find(id)->second->is_admin();
}

int Database::remove_user(uint id)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
        User* u = users.find(id)->second;
        if( u->get_id() == id) return remove_user(u);
        else return -3;
        } return -1;
    } return -44;
}

int Database::remove_user(User* u)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            int id = u->get_id();
            delete u;
            users.erase(id);
            #ifdef _Debug
            std::cout << "Removing user id: " << id << std::endl;
            #endif
            return 0;
        }
        else return -1;
    } return -44;
}

User* Database::get_user(uint id) const
{
    User* u = users.find(id)->second;
    if( u->get_id() == id) return u;
    else throw UserNotFound(id);
}

std::vector<User*> Database::get_users_pointers() const
{
    std::vector<User*>  vec;
    for(auto& u: users)
    {
        vec.push_back(u.second);
    }
    return vec;
    
}

std::vector<std::pair<uint, std::string>> Database::get_users() const
{
    std::vector<std::pair<uint, std::string>> vec;
    if(currently_logged)
    {
        for(auto& u: users)
        {
            vec.push_back(std::pair<uint, std::string>(u.second->get_id(), u.second->get_name()));
        }
    }
    return vec;  
}

std::string Database::get_user_name(uint id) const
{
    return users.find(id)->second->get_name();
}

int Database::modify_research(uint id, Research* r)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            researchs.find(id)->second->operator=(*r);
            return 0;
        }
        else return -1;
    } return -44;
}

int Database::add_research_point(uint research_id, std::string title, bool is_req)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            ResearchPoint *p = new ResearchPoint(title, is_req, next_research_point_id);
            ++next_research_point_id;
            researchs.find(research_id)->second->add_researchPoint(p);
            return 0;
        }   return -1;
    } return -44;
}


int Database::add_sensor_research(uint research_id, uint researchPoint_id, std::string lable, std::string type, std::string unit)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            int sid = add_sensor(lable, type, unit);
            researchs.find(research_id)->second->get_researchPoint(researchPoint_id)->add_sensor(sid);
            return sid;
        }   return -1;
    } return -44;
}

int Database::add_sensor_research(uint research_id, uint researchPoint_id ,uint sensor_id)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            researchs.find(research_id)->second->get_researchPoint(researchPoint_id)->add_sensor(sensor_id);
            return sensor_id;
        }   return -1;
    } return -44;
}

int Database::remove_sensor_research(uint research_id, uint researchPoint_id ,uint sensor_id)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            researchs.find(research_id)->second->get_researchPoint(researchPoint_id)->delete_sensor(sensor_id);
            return 0;
        }   return -1;
    } return -44;
}


std::vector<Research*> Database::get_researchs_s_d_pointers(Date s_d) const
{ 
    std::vector<Research*> vec;
    if(currently_logged)
    {

        for(auto& r:researchs)
        {
            if(r.second->get_start_date()==s_d)
                vec.push_back(r.second);
        }
       
    }
    return vec;
}

std::vector<Research*> Database::get_researchs_d_d_pointers(Date d_d) const
{
    std::vector<Research*> vec;
    if(currently_logged)
    {
        for(auto& r:researchs)
        {
            if(r.second->get_start_date()==d_d)
                vec.push_back(r.second);
        }
        
    }
    return vec;
}

std::vector<Research*> Database::get_researchs_user_pointers(uint user_id)  const
{
    std::vector<Research*> vec;
    if(currently_logged)
    {
        for(auto& r:researchs)
        {
            std::vector<uint> v =  r.second->get_users_ID();
            if(in_vector(v, user_id))
                vec.push_back(r.second);
        }
        
    }
    return vec;
}

std::vector<Research*> Database::get_researchs_author_pointers(uint user_id) const
{
    std::vector<Research*> vec;
    if(currently_logged)
    {
        for(auto& r:researchs)
        {
            if(r.second->get_author_user() == user_id)
                vec.push_back(r.second);
        }
        
    }
    return vec;
}

std::vector<std::pair<uint, std::string>> Database::get_researchs_s_d(Date s_d) const
{
    std::vector<std::pair<uint, std::string>> vec;
    if(currently_logged)
    {

        for(auto& r:researchs)
        {
            if(r.second->get_start_date()==s_d)
                vec.push_back(std::pair<uint, std::string>(r.second->get_research_ID(), r.second->get_researchTitle()));
        }
    }
    return vec;
}

std::vector<std::pair<uint, std::string>> Database::get_researchs_d_d(Date d_d) const
{
    std::vector<std::pair<uint, std::string>> vec;
    if(currently_logged)
    {
        for(auto& r:researchs)
        {
            if(r.second->get_start_date()==d_d)
                vec.push_back(std::pair<uint, std::string>(r.second->get_research_ID(), r.second->get_researchTitle()));
        }
       
    }
     return vec;
}

std::vector<std::pair<uint, std::string>> Database::get_researchs_user(uint user_id) const
{
    std::vector<std::pair<uint, std::string>> vec;
    if(currently_logged)
    {
        for(auto& r:researchs)
        {
            std::vector<uint> v = r.second->get_users_ID(); 
            if(in_vector(v, user_id))
                vec.push_back(std::pair<uint, std::string>(r.second->get_research_ID(), r.second->get_researchTitle()));
        }
    }
    return vec;
}

std::vector<std::pair<uint, std::string>> Database::get_researchs_author(uint user_id) const
{
    std::vector<std::pair<uint, std::string>> vec;
    if(currently_logged)
    {
        for(auto& r:researchs)
        {
            if(r.second->get_author_user()==user_id)
                vec.push_back(std::pair<uint, std::string>(r.second->get_research_ID(), r.second->get_researchTitle()));
        }
    }
    return vec;
}

int Database::modify_research_title(uint id, std::string title)
{
    if(currently_logged)
    {
        if (currently_logged->is_admin())
        {
        researchs.find(id)->second->change_researchTitle(title);
        return 0;
        }
        else return -1;
    } return -44;
}

int Database::modify_research_state(uint id, std::string state)
{
    if(currently_logged)
    {
        if (currently_logged->is_admin())
        {
            researchs.find(id)->second->set_state(state);
            return 0;
        }
        else return -1;
    } return -44;
}


std::string Database::get_research_title(uint id) const
{
    std::string str = "error";
    str = researchs.find(id)->second->get_researchTitle();
    return str;
}


Date Database::get_research_start_date(uint id) const
{
    return researchs.find(id)->second->get_start_date();
}

Date Database::get_research_end_date(uint id) const
{
    return researchs.find(id)->second->get_deadline_date();
}


std::string Database::get_research_state(uint id) const
{
    return researchs.find(id)->second->get_state();
}


std::vector<uint> Database::get_research_users(uint id) const
{
    return researchs.find(id)->second->get_users_ID();
}


uint Database::get_research_author(uint id) const
{
    return researchs.find(id)->second->get_author_user();
}

int Database::modify_research_start_date(uint id, Date s_d)
{
    if(currently_logged)
    {
        if (currently_logged->is_admin())
        {
            researchs.find(id)->second->set_start_data(s_d);
            return 0;
        }
        else return -1;
    } return -44;
}


int Database::modify_research_end_date(uint id, Date d_d)
{
    if(currently_logged)
    {
        if (currently_logged->is_admin())
        {
            researchs.find(id)->second->change_endline_data(d_d);
            return 0;
        }
        else return -1;
    } return -44;
}

int Database::remove_research_point(uint r_id, uint p_id)
{
    if(currently_logged)
    {
        if(currently_logged->is_admin())
        {
            researchs.find(r_id)->second->delete_researchPoint(p_id);
            return 0;
        }
        else
        {
            return -1;
        }
    } return -44;  
}


int Database::modify_research_point(uint research_id, uint point_id, ResearchPoint* p) 
{
    if(currently_logged)
    {
        if (currently_logged->is_admin())
        {
            researchs.find(research_id)->second->get_researchPoint(point_id)->change_researchPointTitle(p->get_researchPointTitle());
            researchs.find(research_id)->second->get_researchPoint(point_id)->set_sensors(p->get_sensors());
            researchs.find(research_id)->second->get_researchPoint(point_id)->set_required(p->is_requiredMeasurement());
            //researchs.find(research_id)->second->get_researchPoint(point_id)->set_researchPoint_ID(p->get_researchPoint_ID());
            return 0;
        }
        else return -1;
    } return -44;
}


int Database::modify_research_point_title(uint research_id, uint point_id, std::string title) 
{
    if(currently_logged)
    {
        if (currently_logged->is_admin())
        {
            researchs.find(research_id)->second->get_researchPoint(point_id)->change_researchPointTitle(title);
            return 0;
        }
        else return -1;
    } return -44;
}


int Database::modify_research_req(uint research_id, uint point_id, bool req) 
{
    if(currently_logged)
    {
        if (currently_logged->is_admin())
        {
            researchs.find(research_id)->second->get_researchPoint(point_id)->set_required(req);
            return 0;
        }
        else return -1;
    } return -44;
}


int Database::change_checkbox(uint research_id, uint point_id) 
{
    if(currently_logged)
    {
        researchs.find(research_id)->second->get_researchPoint(point_id)->swich_checked();
        return 0;
    }return -44;
}

int Database::set_checkbox(uint research_id, uint point_id, bool checked) 
{
    if(currently_logged)
    {
        researchs.find(research_id)->second->get_researchPoint(point_id)->set_checked(checked);
        return 0;
    }return -44;
}

Sensor* Database::get_sensor(uint id) const
{
    return sensors.find(id)->second;
}

Research* Database::get_research(uint id) const
{
    return researchs.find(id)->second;
}


std::vector<std::pair<uint, std::string>> Database::get_sensors() const
{
    std::vector<std::pair<uint, std::string>> vec;

        for(auto& s:sensors)
        {
            vec.push_back(std::pair<uint, std::string>(s.second->get_sensor_ID(), s.second->get_sensorLabel()));
        }
        return vec;
    return vec;
}

std::vector<ResearchPoint*> Database::get_research_points_pointers(uint id) const
{
    return researchs.find(id)->second->get_researchPoints();
}

std::vector<ResearchPoint*> Database::get_research_points_pointers_sorted(uint id) 
{
    return researchs.find(id)->second->get_researchPoints_sorted();
}

std::vector<std::pair<uint, std::string>> Database::get_research_points(uint id) const
{
    std::vector<std::pair<uint, std::string>> vec;
    for(auto p: researchs.find(id)->second->get_researchPoints())
    {
        vec.push_back(std::pair<uint, std::string>(p->get_researchPoint_ID(), p->get_researchPointTitle()));
    }
    return vec;
}

std::vector<std::pair<uint, std::string>> Database::get_research_points_sorted(uint id)
{
    std::vector<std::pair<uint, std::string>> vec;
    sort_research_points(id);
    for(auto p: researchs.find(id)->second->get_researchPoints_sorted())
    {
        vec.push_back(std::pair<uint, std::string>(p->get_researchPoint_ID(), p->get_researchPointTitle()));
    }
    return vec;
}

std::vector<Sensor*> Database::get_research_point_sensors_pointers(uint r_id, uint p_id) const
{
    std::vector<Sensor*> vec;
    std::vector<uint> ids =  researchs.find(r_id)->second->get_researchPoint(p_id)->get_sensors();
    for(auto id: ids)
        vec.push_back(sensors.find(id)->second);
    return vec;
}

std::vector<std::pair<uint, std::string>> Database::get_research_point_sensors(uint r_id, uint p_id) const
{
    std::vector<std::pair<uint, std::string>> vec;
    std::vector<uint> ids =  researchs.find(r_id)->second->get_researchPoint(p_id)->get_sensors();
    for(auto id: ids)
        vec.push_back(std::pair<uint, std::string>(id, sensors.find(id)->second->get_sensorLabel()));
    return vec;
}

 std::vector<Sensor*> Database::get_sensors_pointers() const
 {
     std::vector<Sensor*> vec;
     for(auto& s:sensors)
     {
         vec.push_back(s.second);
     }
     return vec;
 }

    User* Database::get_currently_loged()
    {
        return currently_logged;
    }