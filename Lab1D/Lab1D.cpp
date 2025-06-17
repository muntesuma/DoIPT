#include <memory>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
using namespace std;

class AbstractEntity {
public:
    virtual ~AbstractEntity() = default;
    virtual string type() const = 0;
};

class AccountEntity : public AbstractEntity {
public:
    string type() const override { return "Account"; }
};

class RoleEntity : public AbstractEntity {
public:
    string type() const override { return "Role"; }
};

class IRepository {
public:
    virtual ~IRepository() = default;
    virtual void save(const AbstractEntity& entity) = 0;
};

class AccountRepository : public IRepository {
public:
    void save(const AbstractEntity& entity) override {
        cout << "Executing Account save logic for: " << entity.type() << endl;
    }
};

class RoleRepository : public IRepository {
public:
    void save(const AbstractEntity& entity) override {
        cout << "Executing Role save logic for: " << entity.type() << endl;
    }
};

class RepositoryManager {
private:
    unordered_map<string, unique_ptr<IRepository>> repositories;

public:
    RepositoryManager() {
        registerRepository("Account", make_unique<AccountRepository>());
        registerRepository("Role", make_unique<RoleRepository>());
    }

    void registerRepository(const string& type, unique_ptr<IRepository> repo) {
        repositories[type] = move(repo);
    }

    void save(const AbstractEntity& entity) {
        auto it = repositories.find(entity.type());
        if (it != repositories.end()) {
            it->second->save(entity);
        }
        else {
            throw runtime_error("No repository registered for type: " + entity.type());
        }
    }
};

void test() {
    RepositoryManager manager;

    AccountEntity account;
    RoleEntity role;

    manager.save(account);
    manager.save(role);
}

int main() {
    test();

    return 0;
}