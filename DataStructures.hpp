#include <vector>
#include <memory>
#include <limits>

class Monster;

class SparseMonsterSet {
private:
    std::vector<int> sparse;
    std::vector<std::unique_ptr<Monster>> dense;
public:
    static constexpr int invalidIndex = -1;

    SparseMonsterSet(int maxId);
    bool containsId(int id) const;
    bool contains(const Monster* monster) const;
    bool insert(std::unique_ptr<Monster> monster);
    bool erase(int id, std::set<int>& available_monster_ids);
    std::vector<std::unique_ptr<Monster>>::iterator begin();
    std::vector<std::unique_ptr<Monster>>::iterator end();
    size_t size() const;
    std::unique_ptr<Monster>& operator[](std::size_t index);
    const std::unique_ptr<Monster>& operator[](std::size_t index) const;
};