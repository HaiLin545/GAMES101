// clang-format off
#include <iostream>
#include <opencv2/opencv.hpp>
#include "rasterizer.hpp"
#include "global.hpp"
#include "Triangle.hpp"

const float MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) {
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], \
                 0, 1, 0, -eye_pos[1], \
                 0, 0, 1, -eye_pos[2], \
                 0, 0, 0, 1;

    view = translate * view;
    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle, Eigen::Vector3f n = {0.0f, 0.0f, 1.0f}) {
    float angle = rotation_angle * MY_PI / 180.0f;
    float cosa = cos(angle);
    float sina = sin(angle);
    Eigen::Matrix3f I = Eigen::Matrix3f::Identity();
    Eigen::Matrix4f model = Eigen::Matrix4f::Zero();
    Eigen::Matrix3f N;

    N << 0, -n[2], n[1], \
         n[2], 0, -n[0], \
         -n[1], n[0], 0;
    N = cosa * I + (1.0 - cosa) * (n * n.transpose()) + sina * N;

    model.block(0, 0, 2, 2) = N.block(0, 0, 2, 2);
    model(3, 3) = 1;

    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar) {
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    float fovY = eye_fov * MY_PI / 180.f;
    float n = -zNear, f = -zFar;
    float t = abs(n) * tan(fovY / 2.f);
    float b = -t;
    float r = t * aspect_ratio;
    float l = -r;

    Eigen::Matrix4f M_persp2ortho;
    M_persp2ortho << n, 0, 0, 0, \
                    0, n, 0, 0, \
                    0, 0, n + f, -n * f, \
                    0, 0, 1, 0;

    Eigen::Matrix4f M_ortho_scale, M_ortho_translate;
    M_ortho_scale << 2.f / (r - l), 0, 0, 0, \
                     0, 2.f / (t - b), 0, 0, \
                     0, 0, 2.f / (n - f), 0, \
                     0, 0, 0, 1;
    M_ortho_translate << 1.f, 0, 0, -(r + l) / 2.f, \
                         0, 1.f, 0, -(t + b) / 2.f, \
                         0, 0, 1.f, -(n + f) / 2.f, \
                         0, 0, 0, 1.f;

    projection = M_ortho_scale * M_ortho_translate * M_persp2ortho * projection;

    return projection;
}


int main(int argc, const char **argv) {
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc == 2) {
        command_line = true;
        filename = std::string(argv[1]);
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};


    std::vector<Eigen::Vector3f> pos
            {
                    {2,   0,   -2},
                    {0,   2,   -2},
                    {-2,  0,   -2},
                    {3.5, -1,  -5},
                    {2.5, 1.5, -5},
                    {-1,  0.5, -5}
            };

    std::vector<Eigen::Vector3i> ind
            {
                    {0, 1, 2},
                    {3, 4, 5}
            };

    std::vector<Eigen::Vector3f> cols
            {
                    {217.0, 238.0, 185.0},
                    {217.0, 238.0, 185.0},
                    {217.0, 238.0, 185.0},
                    {185.0, 217.0, 238.0},
                    {185.0, 217.0, 238.0},
                    {185.0, 217.0, 238.0}
            };

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);
    auto col_id = r.load_colors(cols);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45.f, 1, 0.1, 50));

        r.draw(pos_id, ind_id, col_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, col_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        cv::imshow("image", image);
        key = cv::waitKey(10);

    }

    return 0;
}
// clang-format on