#pragma once

template <typename Repository, typename DatabaseService, typename Entity, typename ExecuteResult, typename LoadResult>
class RepositoryInterface {
public:
  ExecuteResult insert(const Entity& entity) {
      return static_cast<Repository *>(this)->insertImpl(entity);
  }
  ExecuteResult update(const Entity& entity) {
      return static_cast<Repository *>(this)->updateImpl(entity);
  }
  ExecuteResult remove(uint64_t id) {
      return static_cast<Repository *>(this)->removeImpl(id);
  }
  LoadResult getAll() {
      return static_cast<Repository *>(this)->getAllImpl();
  }
  LoadResult getById(uint64_t id) {
      return static_cast<Repository *>(this)->getByIdImpl(id);
  }
};
