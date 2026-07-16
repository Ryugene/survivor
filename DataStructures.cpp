#include "DataStructures.hpp"
#include "Monsters.hpp"



SparseMonsterSet::SparseMonsterSet(int maxId) : sparse(maxId, invalidIndex) {
    dense.reserve(maxId);
}

bool SparseMonsterSet::containsId(int id) const {
    return id < sparse.size() && sparse[id] != invalidIndex;
}

bool SparseMonsterSet::contains(const Monster* monster) const {
    return monster != nullptr && containsId(monster->id);
}

bool SparseMonsterSet::insert(std::unique_ptr<Monster> monster) {
    if (!monster)
        return false;

    const int id = monster->id;

    if (id >= sparse.size())
        return false;

    if (containsId(id))
        return false;

    sparse[id] = dense.size();
    dense.push_back(std::move(monster));

    return true;
}

bool SparseMonsterSet::erase(int id, std::set<int>& available_monster_ids)
{
    if (!containsId(id))
        return false;

    const int removeIndex = sparse[id];
    const int lastIndex = dense.size() - 1;

    if (removeIndex != lastIndex)
    {
        const int lastId = dense[lastIndex]->id;

        dense[removeIndex] = std::move(dense[lastIndex]);
        sparse[lastId] = removeIndex;
    }

    dense.pop_back();
    sparse[id] = invalidIndex;
    available_monster_ids.insert(id);

    return true;
}

std::vector<std::unique_ptr<Monster>>::iterator SparseMonsterSet::begin() { return dense.begin(); }
std::vector<std::unique_ptr<Monster>>::iterator SparseMonsterSet::end() { return dense.end(); }
size_t SparseMonsterSet::size() const { return dense.size(); }

std::unique_ptr<Monster>& SparseMonsterSet::operator[](std::size_t index) { return dense[index]; }
const std::unique_ptr<Monster>& SparseMonsterSet::operator[](std::size_t index) const { return dense[index]; }