#ifndef QGE_ACTION_LIST_H
#define QGE_ACTION_LIST_H

#include "interface/action.h"
#include "utils/jsonFileManager/json_file_manager.h"

#include <string>
#include <map>


namespace quasi_game_engine {

// All buttons should be tied to an ActionEnum
// Any new actions must be inserted before ACTION_NULL, should be given a consequtive
// value and value of ACTION_NULL should be iterated
enum ActionEnum {
  ACTION_UP = 0, ACTION_DOWN = 1, ACTION_RIGHT = 2, ACTION_LEFT = 3,
  ACTION_ESC = 4,
  ACTION_NULL = 5,
  ACTION_MAX = ACTION_NULL
};



class logger; // Allows below class to send logs
class ActionList {
/*------------------------------------------------------------------------------
Responsbile for storing, updating, setting and getting the list of actions that
can be activated by a button press.
Notes:
- May need to handle memory of buttons pressed?
- There may be a bug if a button is not set in the file and then someone
tries to access that button...
- Need to eventually save the action list to file
------------------------------------------------------------------------------*/
 public:
  ActionList(Logger logger);
  ~ActionList() = default;

  //Getting rid of copy/move constructors/assignment operators (may need later)
  ActionList(const ActionList&) = delete;
  ActionList& operator=(const ActionList&) = delete;
  ActionList(ActionList&&) = delete;
  ActionList& operator=(ActionList&&) = delete;

  void LoadActionMapping(const char *config_file_name);
  void ReloadActionMapping();

  // This may be removed in favour for a static function with active_buttons_as input also
  bool IsActionActive(const ActionEnum action) const;

  void SetAction(ActionEnum action, int button_value,
                 bool is_hold, const char* name = "");
  // ActionEnum has integer equivilent, which is used when reading from file
  void SetAction(int action, int button_value,
                 bool is_hold, const char* name = "");
  //TODO: cant set as const function...
  const Action GetAction(ActionEnum action) const;
  const Action GetAction(const char* name) const;

  void Update(int new_button_state);
  const std::map<ActionEnum, Action> GetActions() const { return actions_; };

 private:
  int action_state_, hold_actions_, active_actions_;
  std::map<ActionEnum, Action> actions_;
  ButtonTypeEnum set_input_;

  Logger logger_;
  JsonFileManager json_file_manager_;

  void ParseActions(JsonFile* config_file);
  void SetBitOrder();
  ButtonTypeEnum GetButtonEnumFromString(const char* input_type_str) const;
};

} // namespace quasi_game_engine


#endif // QGE_ACTION_LIST_H
