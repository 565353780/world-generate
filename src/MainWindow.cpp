#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <time.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    run_example();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_example()
{
    // 0 : AnHui Applicated Center
    // 1 : Rebuild Demo
    // 2 : Rebuild Demo reset room position speed test // offline 130w fps render 700 fps
    // 3 : Rebuild Demo all process speed test // offline 56w fps render 700 fps
    size_t demo_mode = 0;

    timespec t_spc;
    clock_gettime(CLOCK_REALTIME_COARSE, &t_spc);
    long t_start = t_spc.tv_sec;
    long last_secont = t_start;

    size_t cycle_num = 0;
    float average_fps = 0;

    SpaceController space_controller;

    switch(demo_mode)
    {
    case 0:
        space_controller.createBoundary("Outer Wall");
        space_controller.setOuterBoundary(0);

        space_controller.addBoundaryPoint(0, 0, 0);
        space_controller.addBoundaryPoint(0, 400, 0);
        space_controller.addBoundaryPoint(0, 400, 200);
        space_controller.addBoundaryPoint(0, 160, 200);
        space_controller.addBoundaryPoint(0, 160, 400);
        space_controller.addBoundaryPoint(0, 400, 400);
        space_controller.addBoundaryPoint(0, 400, 800);
        space_controller.addBoundaryPoint(0, 0, 800);

        space_controller.updateBoundary();

        space_controller.createRoom("Meeting Room");
        space_controller.setRoomSize(0, 100, 100);
        space_controller.createRoom("Gaming Room");
        space_controller.setRoomSize(1, 100, 100);
        space_controller.createRoom("Manager Department");
        space_controller.setRoomSize(2, 100, 100);
        space_controller.createRoom("Manager Department");
        space_controller.setRoomSize(3, 100, 100);
        space_controller.createRoom("Gaming Room");
        space_controller.setRoomSize(4, 100, 100);
        space_controller.createRoom("Meeting Room");
        space_controller.setRoomSize(5, 100, 100);

        space_controller.setRoomNeighboor(0, 1);
        space_controller.setRoomNeighboor(1, 2);
        space_controller.setRoomNeighboor(0, 2);

        space_controller.setRoomNeighboor(3, 4);
        space_controller.setRoomNeighboor(4, 5);

        space_controller.updateRoomConnection();

        space_controller.setRoomBoundaryPointParam(0, 0, 0, 0);
        space_controller.setRoomBoundaryPointParam(4, 0, 6, 0);

        space_controller.updateRoom();

        space_controller.showSpace(0);

        break;
    case 1:
        space_controller.createBoundary("Outer Wall");
        space_controller.setOuterBoundary(0);

        space_controller.addBoundaryPoint(0, 0, 0);
        space_controller.addBoundaryPoint(0, 400, 0);
        space_controller.addBoundaryPoint(0, 400, 400);
        space_controller.addBoundaryPoint(0, 0, 400);

        space_controller.updateBoundary();

        space_controller.createRoom("MR 1");
        space_controller.setRoomSize(0, 100, 70);
        space_controller.createRoom("MR 2");
        space_controller.setRoomSize(1, 100, 70);
        space_controller.createRoom("MR 3");
        space_controller.setRoomSize(2, 100, 80);

        space_controller.setRoomNeighboor(0, 1);
        space_controller.setRoomNeighboor(1, 2);

        space_controller.createRoom("MR 4");
        space_controller.setRoomSize(3, 100, 100);
        space_controller.createRoom("MR 5");
        space_controller.setRoomSize(4, 100, 100);

        space_controller.updateRoomConnection();

        space_controller.setRoomBoundaryPointParam(2, 0, 0, 1);
        space_controller.setRoomBoundaryPointParam(3, 0, 2, 0);
        space_controller.setRoomBoundaryPointParam(4, 0, 2, 1);

        space_controller.updateRoom();

        space_controller.showSpace(0);

        break;
    case 2:
        space_controller.createBoundary("Outer Wall");
        space_controller.setOuterBoundary(0);

        space_controller.addBoundaryPoint(0, 0, 0);
        space_controller.addBoundaryPoint(0, 400, 0);
        space_controller.addBoundaryPoint(0, 400, 400);
        space_controller.addBoundaryPoint(0, 0, 400);

        space_controller.updateBoundary();

        space_controller.createRoom("MR 1");
        space_controller.setRoomSize(0, 100, 70);
        space_controller.createRoom("MR 2");
        space_controller.setRoomSize(1, 100, 70);
        space_controller.createRoom("MR 3");
        space_controller.setRoomSize(2, 100, 80);

        space_controller.setRoomNeighboor(0, 1);
        space_controller.setRoomNeighboor(1, 2);

        space_controller.createRoom("MR 4");
        space_controller.setRoomSize(3, 100, 100);
        space_controller.createRoom("MR 5");
        space_controller.setRoomSize(4, 100, 100);

        space_controller.updateRoomConnection();

        while(true)
        {
            size_t random_room_2_boundary_line_idx = std::rand() % 4;
            size_t random_room_34_boundary_line_idx = (random_room_2_boundary_line_idx + 2) % 4;
            float random_room_2_boundary_line_param = 1.0 * (std::rand() % 1000) / 1000.0;
            float random_room_3_boundary_line_param = 1.0 * (std::rand() % 300) / 1000.0;
            float random_room_4_boundary_line_param = 0.7 + 1.0 * (std::rand() % 300) / 1000.0;
            space_controller.setRoomBoundaryPointParam(2, 0, random_room_2_boundary_line_idx, random_room_2_boundary_line_param);
            space_controller.setRoomBoundaryPointParam(3, 0, random_room_34_boundary_line_idx, random_room_3_boundary_line_param);
            space_controller.setRoomBoundaryPointParam(4, 0, random_room_34_boundary_line_idx, random_room_4_boundary_line_param);

            space_controller.updateRoom();

            space_controller.showSpace(1);

            ++cycle_num;

            clock_gettime(CLOCK_REALTIME_COARSE, &t_spc);
            long t_end = t_spc.tv_sec;

            if(t_end == last_secont)
            {
                continue;
            }
            last_secont = t_end;

            average_fps = 1.0 * cycle_num / (t_end - t_start);

            std::cout << "fps : " << size_t(average_fps) << std::endl;
        }

        break;
    case 3:
        while(true)
        {
            space_controller.reset();

            space_controller.createBoundary("Outer Wall");
            space_controller.setOuterBoundary(0);

            space_controller.addBoundaryPoint(0, 0, 0);
            space_controller.addBoundaryPoint(0, 400, 0);
            space_controller.addBoundaryPoint(0, 400, 400);
            space_controller.addBoundaryPoint(0, 0, 400);

            space_controller.updateBoundary();

            space_controller.createRoom("MR 1");
            space_controller.setRoomSize(0, 100, 70);
            space_controller.createRoom("MR 2");
            space_controller.setRoomSize(1, 100, 70);
            space_controller.createRoom("MR 3");
            space_controller.setRoomSize(2, 100, 80);

            space_controller.setRoomNeighboor(0, 1);
            space_controller.setRoomNeighboor(1, 2);

            space_controller.createRoom("MR 4");
            space_controller.setRoomSize(3, 100, 100);
            space_controller.createRoom("MR 5");
            space_controller.setRoomSize(4, 100, 100);

            space_controller.updateRoomConnection();

            size_t random_room_2_boundary_line_idx = std::rand() % 4;
            size_t random_room_34_boundary_line_idx = (random_room_2_boundary_line_idx + 2) % 4;
            float random_room_2_boundary_line_param = 1.0 * (std::rand() % 1000) / 1000.0;
            float random_room_3_boundary_line_param = 1.0 * (std::rand() % 300) / 1000.0;
            float random_room_4_boundary_line_param = 0.7 + 1.0 * (std::rand() % 300) / 1000.0;
            space_controller.setRoomBoundaryPointParam(2, 0, random_room_2_boundary_line_idx, random_room_2_boundary_line_param);
            space_controller.setRoomBoundaryPointParam(3, 0, random_room_34_boundary_line_idx, random_room_3_boundary_line_param);
            space_controller.setRoomBoundaryPointParam(4, 0, random_room_34_boundary_line_idx, random_room_4_boundary_line_param);

            space_controller.updateRoom();

            space_controller.showSpace(1);

            ++cycle_num;

            clock_gettime(CLOCK_REALTIME_COARSE, &t_spc);
            long t_end = t_spc.tv_sec;

            if(t_end == last_secont)
            {
                continue;
            }
            last_secont = t_end;

            average_fps = 1.0 * cycle_num / (t_end - t_start);

            std::cout << "fps : " << size_t(average_fps) << std::endl;
        }

        break;
    }
}

