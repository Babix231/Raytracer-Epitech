/*
** EPITECH PROJECT, 2023
** raytracerTest
** File description:
** parser
*/

#include "parser.hpp"
void parser::execute()
{
    std::ifstream file(_file);
    std::string line;
    if (!file.is_open())
        throw ParserException("Error: File not found");
    if (_file.substr(_file.find_last_of(".") + 1) != "cfg" && _file.substr(_file.find_last_of(".") + 1) != "obj")
        throw ParserException("Error: File is not a .cfg");

    libconfig::Config cfg;
    try {
        cfg.readFile(_file.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        throw ParserException("Error: I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        throw ParserException("Error: Parse errodzdr at");
    }
    file.close();
    if (!cfg.exists("camera")) {
        _cameraConfig.fov = 60.0;
        _cameraConfig.width = 500;
        _cameraConfig.height = 500;
        _cameraConfig.position.x = 1.0;
        _cameraConfig.position.y = -0.0;
        _cameraConfig.position.z = -10.0;
        _cameraConfig.rotation.x = 0.0;
        _cameraConfig.rotation.y = 0.0;
        _cameraConfig.rotation.z = 0.0;
    } else {
    try {
        libconfig::Setting& camera = cfg.lookup("camera");
        camera.lookupValue("fieldOfView", _cameraConfig.fov);
        libconfig::Setting& resolution = camera.lookup("resolution");
        resolution.lookupValue("width", _cameraConfig.width);
        resolution.lookupValue("height", _cameraConfig.height);
        libconfig::Setting& position = camera.lookup("position");
        position.lookupValue("x", _cameraConfig.position.x);
        position.lookupValue("y", _cameraConfig.position.y);
        position.lookupValue("z", _cameraConfig.position.z);
        libconfig::Setting& rotation = camera.lookup("rotation");
        rotation.lookupValue("x", _cameraConfig.rotation.x);
        rotation.lookupValue("y", _cameraConfig.rotation.y);
        rotation.lookupValue("z", _cameraConfig.rotation.z);
    } catch (const libconfig::SettingNotFoundException& nfex) {
        std::cerr << "Error: Setting not found" << std::endl;
    }
    }
    try {
        std::vector<std::string> listofprimitive = {"plane","sphere","cube","cylindre", "configfile", "triangle","objfile"};
        libconfig::Setting& primitives = cfg.lookup("primitives");
        for (size_t j = 0; j < listofprimitive.size(); j++) {
            if (primitives.exists(listofprimitive[j])) {
                libconfig::Setting& primitive = primitives.lookup(listofprimitive[j]);
                for (int i = 0; i < primitive.getLength(); i++) {
                    Settings settings;
                    settings.type = listofprimitive[j];
                    if (settings.type == "configfile") {
                        for (int i = 0; i < primitive.getLength(); i++) {
                            std::string filename;
                            double scale = 1.0;
                            double x,y,z = 0.0;
                            libconfig::Setting& file = primitive[i];
                            file.lookupValue("path", filename);
                            file.lookupValue("x", x);
                            file.lookupValue("y", y);
                            file.lookupValue("z", z);
                            vec3 tmpposition = vec3(x, y, z);
                            file.lookupValue("scale", scale);
                            parser parser(filename);
                            parser.execute();
                            std::vector<Settings> hittable = parser._hittable;
                            for (size_t i = 0; i < hittable.size(); i++) {
                                hittable[i].position = hittable[i].position * scale;
                                hittable[i].position = hittable[i].position + tmpposition;
                                if (hittable[i].properties["size"] != "")
                                    hittable[i].properties["size"] = std::to_string(std::stod(hittable[i].properties["size"]) * scale);
                            }
                            if (file.exists("repeat")) {
                                int nb = 0;
                                double x = 0;
                                double y = 0;
                                double z = 0;
                                libconfig::Setting& repeat = file.lookup("repeat");
                                if (repeat.exists("nb"))
                                    repeat.lookupValue("nb", nb);
                                if (repeat.exists("x"))
                                    repeat.lookupValue("x", x);
                                if (repeat.exists("y"))
                                    repeat.lookupValue("y", y);
                                if (repeat.exists("z"))
                                    repeat.lookupValue("z", z);
                                vec3 tmp = vec3(x, y, z);
                                for (int i = 0; i < nb; i++) {
                                    for (size_t i = 0; i < hittable.size(); i++) {
                                        hittable[i].position = hittable[i].position + tmp;
                                        _hittable.push_back(hittable[i]);
                                    }
                                }
                            }
                            for (size_t i = 0; i < hittable.size(); i++)
                                _hittable.push_back(hittable[i]);
                            continue;
                        }
                    }
                    if (settings.type == "objfile") {
                            libconfig::Setting& primitiveSettings =primitive[i];
                            double x, y, z = 0.0;
                            std::string filename;
                            primitiveSettings.lookupValue("path", filename);
                            primitiveSettings.lookupValue("x", x);
                            primitiveSettings.lookupValue("y", y);
                            primitiveSettings.lookupValue("z", z);
                            settings.position = vec3(x / 10.0, y / 10.0, z / 10.0);
                            libconfig::Setting& color =
                            primitiveSettings.lookup("color");
                            color.lookupValue("material", settings.material);
                            double r, g, b = 0.0;
                            color.lookupValue("r", r);
                            color.lookupValue("g", g);
                            color.lookupValue("b", b);
                            settings.color = vec3(r, g, b);
                            settings.properties["path"] = filename;
                            _hittable.push_back(settings);
                            continue;
                    }
                    libconfig::Setting& primitiveSettings = primitive[i];
                    double x,y,z = 0.0;
                    primitiveSettings.lookupValue("x", x);
                    primitiveSettings.lookupValue("y", y);
                    primitiveSettings.lookupValue("z", z);
                    settings.position = vec3(x / 10.0, y/ 10.0, z/ 10.0);
                    libconfig::Setting& color = primitiveSettings.lookup("color");
                    color.lookupValue("material", settings.material);
                    double r,g,b = 0.0;
                    color.lookupValue("r", r);
                    color.lookupValue("g", g);
                    color.lookupValue("b", b);
                    settings.color = vec3(r, g, b);
                    libconfig::Setting& properties = primitiveSettings.lookup("properties");
                    for (int j = 0; j < properties.getLength(); j++) {
                        libconfig::Setting& property = properties[j];
                        std::string name = property.getName();
                        double value = property;
                        settings.properties[name] = std::to_string(value);
                    }
                    if (primitiveSettings.exists("repeat")) {
                        double x,y,z = 0.0;
                        double r,g,b = 0.0;
                        int nb = 0;
                        libconfig::Setting& repeat = primitiveSettings.lookup("repeat");
                        if (repeat.exists("nb"))
                            repeat.lookupValue("nb", nb);
                        if (repeat.exists("x"))
                            repeat.lookupValue("x", x);
                        if (repeat.exists("y"))
                            repeat.lookupValue("y", y);
                        if (repeat.exists("z"))
                            repeat.lookupValue("z", z);
                        if (repeat.exists("r"))
                            repeat.lookupValue("r", r);
                        if (repeat.exists("g"))
                            repeat.lookupValue("g", g);
                        if (repeat.exists("b"))
                            repeat.lookupValue("b", b);
                        for (int i = 1; i < nb; i++) {
                            Settings newSettings = settings;
                            newSettings.position = vec3(newSettings.position.x() + (x * i), newSettings.position.y() + (y * i), newSettings.position.z() + (z * i));
                            newSettings.color = vec3(newSettings.color.x() + (r * i), newSettings.color.y() + (g * i), newSettings.color.z() + (b * i));
                            std::cerr << newSettings.position << std::endl;
                            _hittable.push_back(newSettings);
                        }
                    }
                    _hittable.push_back(settings);
                }
            }
        }
    } catch (const libconfig::SettingNotFoundException& nfex) {
        std::cerr << "Error: Setting not found" << std::endl;
    }
}