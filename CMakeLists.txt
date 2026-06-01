# Link to SQLiteCpp as before
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp-3.3.3)

# --- Modern way to find system libraries ---
find_package(Threads REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main
  SQLiteCpp        # Your local library
  sqlite3          # SQLite
  Threads::Threads # Handles pthread and dl for all platforms
)