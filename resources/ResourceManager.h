#pragma once

#include <unordered_map>
#include <string>

template<typename Resource>
class ResourceManager {
	
	using cpString = const std::string&;

public:
	ResourceManager(cpString folder, cpString extention) : _folder("../res/" + folder + "/"), _extention("." + extention) {

	}

	const Resource& get(cpString name) {
		if (!exists(name)) {
			add(name);
		}
		return _resources.at(name);
	}

	bool exists(cpString name) const {
		return _resources.find(name) != _resources.end();
	}

	void add(cpString name) {
		Resource r;

		//if the resource fails to load, then add a "fail" resource
		if (!r.loadFromFile(getFullPath(name))) {
			Resource fail;
			fail.loadFromFile(_folder + "_fail" + _extention);
			_resources.insert(std::make_pair(name, fail));
		}
	}



private:
	std::string getFullPath(cpString name) {
		return _folder + name + _extention;
	}

	const std::string _folder;
	const std::string _extention;

	std::unordered_map<std::string, Resource> _resources;
};