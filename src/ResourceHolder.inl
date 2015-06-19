#include "ResourceHolder.h"


template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder(const std::string& folder) {
    this->folder = folder;
}


template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename) {
    // Creating and load resource
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(folder + filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    // If loading successful than insert resource to map
    auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}


template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename, const Parameter &secondParam) {
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(folder + filename, secondParam))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}


template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) {
    #ifndef NDEBUG
        auto found = resourceMap.find(id);
        assert(found != resourceMap.end());
        return *found->second;
    #else
        return *resourceMap.find(id)->second;
    #endif
}


template <typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    #ifndef NDEBUG
        auto found = resourceMap.find(id);
        assert(found != resourceMap.end());
        return *found->second;
    #else
        return *resourceMap.find(id)->second;
    #endif
}
