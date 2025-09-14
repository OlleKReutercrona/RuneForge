@echo off

call git submodule update --init --recursive

REM Ensure the destination folder exists
if not exist Source\External\Include\nlohmann mkdir Source\External\Include\nlohmann

curl -sS -L https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp -o Source/External/Include/nlohmann/json.hpp
curl -sS -L https://github.com/nlohmann/json/releases/download/v3.11.3/json_fwd.hpp -o Source/External/Include/nlohmann/json_fwd.hpp