#ifndef SFML_GAME_DEVELOPMENT_RESOURCEHOLDER_H
#define SFML_GAME_DEVELOPMENT_RESOURCEHOLDER_H

#include <map>
#include <memory>
#include <string>
#include <cassert>


template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    ResourceHolder(const std::string& folder);
    void load(Identifier id, const std::string &filename);
    template<typename Parameter>
    void load(Identifier id, const std::string &filename, const Parameter &secondParam);
    Resource &get(Identifier id);
    const Resource &get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
    std::string folder;
};

#include "ResourceHolder.inl"

#endif
