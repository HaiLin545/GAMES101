#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) {
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
            -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle, Eigen::Vector3f n = {0.0f, 0.0f, 1.0f}) {
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.

    double angle = rotation_angle * MY_PI / 180;
    double cosa = cos(angle);
    double sina = sin(angle);
    Eigen::Matrix3f I = Eigen::Matrix3f::Identity();
    Eigen::Matrix4f M = Eigen::Matrix4f::Zero();
    Eigen::Matrix3f N;

    N << 0, -n[2], n[1],
            n[2], 0, -n[0],
            -n[1], n[0], 0;
    N = cosa * I + (1.0 - cosa) * (n * n.transpose()) + sina * N;

    M.block(0, 0, 2, 2) = N.block(0, 0, 2, 2);
    M(3, 3) = 1;

    model = M * model;

    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar) {
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.

    float fovY = eye_fov * MY_PI / 180;
    float n = -zNear, f = -zFar;
    float t = abs(n) * tan(fovY / 2.0);
    float b = -t;
    float r = t * aspect_ratio;
    float l = -r;

    Eigen::Matrix4f M_persp;
    M_persp << n, 0, 0, 0,
            0, n, 0, 0,
            0, 0, n + f, -n * f,
            0, 0, 1, 0;

    Eigen::Matrix4f M_ortho_s;
    M_ortho_s << 2.0 / (r - l), 0, 0, 0,
            0, 2.0 / (t - b), 0, 0,
            0, 0, 2.0 / (n - f), 0,
            0, 0, 0, 1;

    projection = M_ortho_s * M_persp * projection;

    return projection;
}

int main(int argc, const char **argv) {
    float angle_z = 0, angle_x = 0;
    bool is_axis_z = true, is_asis_x = false;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle_z = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};
    Eigen::Vector3f z = {0, 0, 1.0};
    Eigen::Vector3f x = {1.0, 0, 0};
    Eigen::Vector3f y = {0, 1.0, 0};

    std::vector<Eigen::Vector3f> pos{{2,  0, -2},
                                     {0,  2, -2},
                                     {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {

        r.clear(rst::Buffers::Color | rst::Buffers::Depth);
        r.set_model(get_model_matrix(angle_z));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());

        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    Eigen::Vector3f rotate_axis = z;

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(is_axis_z ? angle_z : angle_x, rotate_axis));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        switch (key) {
            case 'a':
                is_axis_z = true;
                rotate_axis = z;
                angle_z += 10;
                break;
            case 'd':
                is_axis_z = true;
                rotate_axis = z;
                angle_z -= 10;
                break;
            case 'w':
                is_axis_z = false;
                rotate_axis = x;
                angle_x += 10;
                break;
            case 's':
                is_axis_z = false;
                rotate_axis = x;
                angle_x -= 10;
                break;
            default:
                break;
        }

    }

    return 0;
}
