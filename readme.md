# Run
- Create Redis module: `make module.so`
- Run tests: `make tests`

# Usage
- `redis-server --loadmodule module.so`

# Tasks
- [x] Accept numbers in trie
- [x] Add remove to Redis module
- [ ] Accept multiple args in insert
- [ ] Return remove result as 0 (didn't exist) or 1 (existed and removed)

# Resources
- [Redis Modules: an introduction to the API](https://redis.io/topics/modules-intro)
- [Writing Redis Modules](https://redislabs.com/blog/writing-redis-modules/)
- [Extend Redis with Modules](https://www.slideshare.net/itamarhaber/redis-modules-an-introduction-to-users-developers) - Slides

## Sample codes
- [Redis module sample](https://github.com/antirez/redis/blob/fc0c9c8097a5b2bc8728bec9cfee26817a702f09/src/modules/hellotype.c)
    - This file implements a new module native data type called "HELLOTYPE".
- [redis-tries](https://github.com/cmsc22000-project-2018/redis-tries) module