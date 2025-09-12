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

		/// <summary>
		/// Tries to extract a value from a given json object using the specified key.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="json">JSON object to extract data from</param>
		/// <param name="key">Name of the wanted value</param>
		/// <param name="defaultValue">A default value to fall back on if key doesn't excist</param>
		/// <returns></returns>
		template<typename T>
		T TryGet(const nlohmann::json& json, const std::string& key, const T& defaultValue) {
			if(!json.contains(key)) {
				return defaultValue;
			}

			return json.at(key).get<T>();
		}
	}
}