#include "stdafx.h"
#include <nlohmann/json.hpp>
#include "jsonUtil.h"

namespace RF::Json {
	constexpr std::string_view gJson = ".json";

	bool isJson(const std::string& directory) {
		auto strPos = directory.find_last_of('.');
		std::string lineEnding(directory.begin() + strPos, directory.end());

		return lineEnding == gJson;
	}
}


nlohmann::json RF::Json::Parse(const std::string& directory) {
	if (!isJson(directory)) {
		return {};
	}

	std::ifstream file(directory);
	if (!file.good()) {
		// TODO: Put output error message here
		file.close();
		return {};
	}

	// Technically this create an extra copy of the JSON object, but it is needed to close the file in here
	auto obj = nlohmann::json::parse(file);
	file.close();
	return obj;
}

void RF::Json::Serialize(const std::string& directory, const nlohmann::json& obj) {
	if (!isJson(directory)) {
		return;
	}

	std::ofstream file(directory);
	if (!file.good()) {
		return;
	}

	file << obj;
	file.close();
}
