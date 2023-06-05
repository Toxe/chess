add_library(lib_chess
    ai/receive_ai_command.cpp
    ai/receive_ai_command.hpp
    app/app_controller.cpp
    app/app_controller.hpp
    app/commands.cpp
    app/commands.hpp
    board/board.cpp
    board/board.hpp
    board/file.hpp
    board/print.cpp
    board/print.hpp
    board/rank.cpp
    board/rank.hpp
    board/square.cpp
    board/square.hpp
    command/command.hpp
    command/command_factory.cpp
    command/command_factory.hpp
    game/castling_ability.hpp
    game/commands.cpp
    game/commands.hpp
    game/game_players.cpp
    game/game_players.hpp
    game/move.cpp
    game/move.hpp
    game/pieces.cpp
    game/pieces.hpp
    game/player.cpp
    game/player.hpp
    game/print.cpp
    game/print.hpp
    game/win_conditions.cpp
    game/win_conditions.hpp
    grid/coords.hpp
    grid/grid.hpp
    grid/gridcell.hpp
    input/eval_input.cpp
    input/eval_input.hpp
    input/receive_player_command.cpp
    input/receive_player_command.hpp
    move_generator/game_state.cpp
    move_generator/game_state.hpp
    move_generator/legal_moves.cpp
    move_generator/legal_moves.hpp
    move_generator/list_moves.cpp
    move_generator/list_moves.hpp
    move_generator/list_moves_detail.hpp
    move_generator/move_generator.cpp
    move_generator/move_generator.hpp
    move_generator/moves.cpp
    move_generator/moves.hpp
    move_generator/print.cpp
    move_generator/print.hpp
    notation/fen.cpp
    notation/fen.hpp
    notation/fen_detail.cpp
    notation/fen_detail.hpp
    output/console_writer.cpp
    output/console_writer.hpp
    perft/perft.cpp
    perft/perft.hpp
    perft/perft_divide.cpp
    perft/perft_divide.hpp
    perft/print.cpp
    perft/print.hpp
)

set_target_properties(lib_chess PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(lib_chess PUBLIC cxx_std_23)
target_compile_options(lib_chess PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(lib_chess PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(lib_chess PRIVATE ${SANITIZER_LINK_LIBRARIES} fmt::fmt tl::expected)
target_include_directories(lib_chess INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(lib_chess PROPERTIES FOLDER "Chess")
get_target_property(lib_chess_sources lib_chess SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${lib_chess_sources})

# main executable
add_executable(chess main.cpp)
set_target_properties(chess PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(chess PUBLIC cxx_std_23)
target_compile_options(chess PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(chess PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(chess PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_chess)

set_target_properties(chess PROPERTIES FOLDER "Chess")
get_target_property(chess_sources chess SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${chess_sources})
