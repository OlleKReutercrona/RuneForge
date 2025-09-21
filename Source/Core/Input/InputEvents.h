#pragma once
#include <string>
#include <string_view>
#include <unordered_map>

namespace RF {

	namespace input {


#define ENUM_DECLARE(name) name, // Used to convert to enum
#define CASE_ENUM_TO_STRING(name) case InputEvent::name: return #name; // Used to convert enum to string
#define IF_STRING_TO_ENUM(name) if(actionStrConstant == #name) return InputActionID::name; // Used to convert string to enum
#define STR_DECLARE(name) inline constexpr std::string_view name## = #name; // Used to create string constants
#define MAP_ENUM_TO_STRING(name) { #name, InputEvent::name }, // Used to create map entries for string to enum conversion.

		// Centralized list of all input actions.
		// - This list is used to generate enum values and string constants.
#define INPUT_EVENT_LIST(FUNC) \
	    FUNC(Player_MoveForward)    \
	    FUNC(Player_MoveBackward)   \
	    FUNC(Player_MoveLeft)		\
	    FUNC(Player_MoveRight)		\
	    FUNC(Player_Jump)           \
	    FUNC(Player_Attack)         \
	    FUNC(UI_OpenInventory)      \
	    FUNC(UI_CloseMenu)          \
	    FUNC(UI_Select)				\

	// Creates string constants for each action
		INPUT_EVENT_LIST(STR_DECLARE);

	// Creates enum value for each Action

		enum class InputEvent : uint16_t {
			INPUT_EVENT_LIST(ENUM_DECLARE)
			Count
		};

		inline const char *InputActionIdToString(InputEvent action) {
			switch (action) {
				INPUT_EVENT_LIST(CASE_ENUM_TO_STRING)
				default: return "Unknown";
			}
		}

		inline InputEvent InputActionStringToActionId(const std::string &actionStrConstant) {

			static const std::unordered_map<std::string, InputEvent> map = {
				INPUT_EVENT_LIST(MAP_ENUM_TO_STRING)
			};

			auto it = map.find(actionStrConstant);
			return it != map.end() ? it->second : InputEvent::Count;
		}

#undef ENUM_DECLARE
#undef CASE_ENUM_TO_STRING
#undef IF_STRING_TO_ENUM
#undef STR_DECLARE
#undef MAP_ENUM_TO_STRING
	}
}
