@echo off

call git submodule update --init --recursive

curl -sS -L https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp -o Source/External/Include/nlohmann/json.hpp

curl -sS -L https://github.com/nlohmann/json/releases/download/v3.11.3/json_fwd.hpp -o Source/External/Include/nlohmann/json_fwd.hpp