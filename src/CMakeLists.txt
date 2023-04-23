add_library(lib_chess
    app/app_controller.cpp
    app/app_controller.hpp
    app/commands.cpp
    app/commands.hpp
    board/board.cpp
    board/board.hpp
    board/square.cpp
    board/square.hpp
    command/command.hpp
    command/command_factory.cpp
    command/command_factory.hpp
    game/castling_ability.hpp
    game/game_players.cpp
    game/game_players.hpp
    game/move.hpp
    game/pieces.cpp
    game/pieces.hpp
    game/player.cpp
    game/player.hpp
    game/win_conditions.cpp
    game/win_conditions.hpp
    grid/coords.hpp
    grid/grid.hpp
    grid/gridcell.hpp
    input/eval_input.cpp
    input/eval_input.hpp
    input/receive_player_command.cpp
    input/receive_player_command.hpp
    notation/fen.cpp
    notation/fen.hpp
    notation/fen_detail.cpp
    notation/fen_detail.hpp
    output/console_writer.cpp
    output/console_writer.hpp
    output/player_side.cpp
    output/player_side.hpp
    output/print_board.cpp
    output/print_board.hpp
    output/print_game_over.cpp
    output/print_game_over.hpp
    output/print_move.cpp
    output/print_move.hpp
    output/print_piece.cpp
    output/print_piece.hpp
    output/print_square.cpp
    output/print_square.hpp
)

set_target_properties(lib_chess PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(lib_chess PUBLIC cxx_std_20)
target_compile_options(lib_chess PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(lib_chess PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(lib_chess PRIVATE ${SANITIZER_LINK_LIBRARIES} fmt::fmt scn::scn tl::expected)
target_include_directories(lib_chess INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# main executable
add_executable(chess main.cpp)
set_target_properties(chess PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(chess PUBLIC cxx_std_20)
target_compile_options(chess PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(chess PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(chess PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_chess)
