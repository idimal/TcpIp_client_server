#include <string>
#include <vector>

struct Data {
    std::string name;
    int state;
    std::string state_string;
    int state_type;
    std::string state_date;
    std::string id;
};

struct PlmlData {
    int version;
    std::vector<Data> states;
};


struct State {
    std::string version;
    int typeState;
};
