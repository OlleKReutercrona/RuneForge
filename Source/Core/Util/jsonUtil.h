#pragma once
namespace RF {
	namespace Json {
		/// <summary>
		/// Parses the contents of the specified directory and returns the result as a JSON object.
		/// </summary>
		/// <param name="directory">The path to the directory to be parsed.</param>
		/// <returns>A nlohmann::json object containing the parsed data from the directory.</returns>
		nlohmann::json Parse(const std::string& directory);

		/// <summary>
		/// Serializes a JSON object to a specified directory.
		/// </summary>
		/// <param name="directory">The path to the directory where the JSON object will be serialized.</param>
		/// <param name="obj">The JSON object to serialize.</param>
		void Serialize(const std::string& directory, const nlohmann::json& obj);
	}
}


