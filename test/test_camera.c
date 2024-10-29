#ifdef TEST

// #include "unity.h"

// #include "camera.h"
// #include "color.h"
// #include "canvas.h"
// #include "ray.h"
// #include "vecmath.h"
// #include "transforms.h"
// #include "world.h"

#include "unity.h"
#include <string.h>
#include "world.h"
#include "ray.h"
#include "vecmath.h"
#include "transforms.h"
#include "color.h"
#include "camera.h"
#include "canvas.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_camera_Create2(void)
{
    Camera2 cam;
    camera_Create2(&cam, 160, 120, M_PI/2.0);

    Matrix4d expected = UNITY_TRANSFORM;
    TEST_ASSERT_EQUAL(160, cam.hsize);
    TEST_ASSERT_EQUAL(120, cam.vsize);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, M_PI/2.0, cam.fov);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &(cam.transform))); 

}

void test_camera_PixelSizeHorizontalCanvas(void)
{
    Camera2 cam;
    camera_Create2(&cam, 200, 125, M_PI/2.0);
    camera_InitPixelSize(&cam);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.01, cam.pixel_size);
}

void test_camera_PixelSizeVerticalCanvas(void)
{
    Camera2 cam;
    camera_Create2(&cam, 125, 200, M_PI/2.0);
    camera_InitPixelSize(&cam);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.01, cam.pixel_size);
}

void test_camera_RayThroughCanvasCenter(void)
{
    Camera2 cam;
    camera_Create2(&cam, 201, 101, M_PI/2.0);
    camera_InitPixelSize(&cam);
    Ray ray;
    camera_RayForPixel(&cam, &ray, 100, 50);

    Tuple4d exp_origin = {0,0,0,1};
    Tuple4d exp_direction = {0,0,-1,0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp_origin, &(ray.origin)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp_direction, &(ray.direction)));
}

void test_camera_RayThroughCanvasCorner(void)
{
    Camera2 cam;
    camera_Create2(&cam, 201, 101, M_PI/2.0);
    camera_InitPixelSize(&cam);
    Ray ray;
    camera_RayForPixel(&cam, &ray, 0, 0);

    Tuple4d exp_origin = {0,0,0,1};
    Tuple4d exp_direction = {0.66519, 0.33259, -0.66851};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp_origin, &(ray.origin)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp_direction, &(ray.direction)));
}

void test_camera_RayOfTransformedCamera(void)
{
    Camera2 cam;
    camera_Create2(&cam, 201, 101, M_PI/2.0);
    camera_InitPixelSize(&cam);

    Matrix4d rotY;
    transforms_GetRotationYMatrix4d(&rotY, M_PI/4.0);
    Matrix4d transl;
    transforms_GetTranslationMatrix4d(&transl, 0, -2, 5);
    vecmath_MultiplyMatrix4d(&rotY, &transl);
    vecmath_CopyMatrix4d(&rotY, &(cam.transform));

    Ray ray;
    camera_RayForPixel(&cam, &ray, 100, 50);

    Tuple4d exp_origin = {0,2,-5,1};
    Tuple4d exp_direction = {sqrt(2.0)/2, 0, -sqrt(2)/2.0, 0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp_origin, &(ray.origin)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp_direction, &(ray.direction)));
}

// void test_camera_RenderWorld(void)
// {
//     World w;
//     world_CreateDefault(&w);

//     Camera2 cam;
//     camera_Create2(&cam, 11, 11, M_PI/2.0);
//     camera_InitPixelSize(&cam);
//     Tuple4d from = {0,0,-5,1};
//     Tuple4d to = {0,0,0,1};
//     Tuple4d up = {0,1,0,0};
//     camera_SetViewTransform(&cam, &from, &to, &up);

//     Canvas canvas;
//     canvas_Create(&canvas, cam.hsize, cam.vsize);
//     camera_RenderImage(&cam, &w, &canvas);
//     canvas_PixelsToPPMFile(&canvas, "RenderWorld11x11.ppm");

//     Color expected = {0.38066, 0.47583, 0.2855};

//     TEST_ASSERT_TRUE(color_AreEqualColors(&expected, canvas_GetColor(&canvas, 5, 5)));
//     canvas_Destroy(&canvas); 
// }

void test_camera_RenderWorldWith6Spheres(void)
{
    // Sphere 1 - floor
    Object floor;

    Color floor_color = {1.0, 0.9, 0.9};
    Material floor_mat;
    ray_CreateMaterial(&floor_mat, &floor_color, 0.1, 0.9, 0, 0);
    ray_CreateSphere(&floor, &floor_mat);

    Matrix4d scale;
    transforms_GetScalingMatrix4d(&scale, 10, 0.01, 10);
    vecmath_CopyMatrix4d(&scale, &(floor.transform));    

    // Sphere 2 - left wall
    Object left_wall;
    ray_CreateSphere(&left_wall, &floor_mat);

    Matrix4d rotY;
    transforms_GetRotationYMatrix4d(&rotY, -M_PI/4.0);
    Matrix4d rotX;
    transforms_GetRotationXMatrix4d(&rotX, M_PI/2.0);
    Matrix4d transl;
    transforms_GetTranslationMatrix4d(&transl, 0,0,5);
    Matrix4d transform;
    vecmath_CopyMatrix4d(&transl, &transform);
    vecmath_MultiplyMatrix4d(&transform, &rotY);
    vecmath_MultiplyMatrix4d(&transform, &rotX);
    vecmath_MultiplyMatrix4d(&transform, &scale);
    vecmath_CopyMatrix4d(&transform, &(left_wall.transform));

    // Sphere 3 - right wall
    Object right_wall;
    ray_CreateSphere(&right_wall, &floor_mat);

    transforms_GetRotationYMatrix4d(&rotY, M_PI/4.0);
    vecmath_CopyMatrix4d(&transl, &transform);
    vecmath_MultiplyMatrix4d(&transform, &rotY);
    vecmath_MultiplyMatrix4d(&transform, &rotX);
    vecmath_MultiplyMatrix4d(&transform, &scale);

    vecmath_CopyMatrix4d(&transform, &(right_wall.transform));
    // Sphere 4 - large middle
    Object middle_sphere;

    Color ms_color = {0.1, 1, 0.5};
    Material ms_mat;
    ray_CreateMaterial(&ms_mat, &ms_color, 0.1, 0.7, 0.3, 200);
    ray_CreateSphere(&middle_sphere, &ms_mat);

    transforms_GetTranslationMatrix4d(&transl, -0.5, 1, 0.5);
    vecmath_CopyMatrix4d(&transl, &(middle_sphere.transform));

    // Sphere 5 - right
    Object right_sphere;

    Color rs_color = {0.5, 1, 0.1};
    Material rs_mat;
    ray_CreateMaterial(&rs_mat, &rs_color, 0.1, 0.7, 0.3, 200);
    ray_CreateSphere(&right_sphere, &rs_mat);

    transforms_GetTranslationMatrix4d(&transl, 1.5, 0.5, -0.5);
    vecmath_CopyMatrix4d(&transl, &transform);
    transforms_GetScalingMatrix4d(&scale, 0.5, 0.5, 0.5);
    vecmath_MultiplyMatrix4d(&transform, &scale);
    vecmath_CopyMatrix4d(&transform, &(right_sphere.transform));

    // Sphere 6 - left
    Object left_sphere;

    Color ls_color = {1, 0.8, 0.1};
    Material ls_mat;
    ray_CreateMaterial(&ls_mat, &ls_color, 0.1, 0.7, 0.3, 200);
    ray_CreateSphere(&left_sphere, &ls_mat);

    transforms_GetTranslationMatrix4d(&transl, -1.5, 0.33, -0.75);
    vecmath_CopyMatrix4d(&transl, &transform);
    transforms_GetScalingMatrix4d(&scale, 0.33, 0.33, 0.33);
    vecmath_MultiplyMatrix4d(&transform, &scale);
    vecmath_CopyMatrix4d(&transform, &(left_sphere.transform));

    // World
    World w;
    w.numberOfObjects = 0;
    world_addObject(&w, &floor);
    world_addObject(&w, &left_wall);
    world_addObject(&w, &right_wall);
    world_addObject(&w, &middle_sphere);
    world_addObject(&w, &left_sphere);
    world_addObject(&w, &right_sphere);

    // Light source
    PointLight light = {{-10,10,-10,1},{1,1,1}};
    w.lightSource = light;

    // Camera
    Camera2 cam;
    camera_Create2(&cam, 600, 300, M_PI/3.0);
    camera_InitPixelSize(&cam);
    Tuple4d from = {0,1.5,-5,1};
    Tuple4d to = {0,1,0,1};
    Tuple4d up = {0,1,0,0};
    camera_SetViewTransform(&cam, &from, &to, &up);
    Canvas canvas;
    canvas_Create(&canvas, cam.hsize, cam.vsize);
    camera_RenderImage(&cam, &w, &canvas);

    canvas_PixelsToPPMFile(&canvas, "Render6Spheres.ppm");
    canvas_Destroy(&canvas); 
}


// void test_camera_Create(void)
// {
//     int w = 640;
//     int h = 480;
//     Color red = {1,0,0};
//     Color black = {0,0,0};
//     Canvas canvas;
//     canvas_Create(&canvas, w, h);

//     float cam_pos_x = 0, cam_pos_y = 0, cam_pos_z = -5;
//     Matrix4d cam_translate;
//     transforms_GetTranslationMatrix4d(&cam_translate, cam_pos_x, cam_pos_y, cam_pos_z);
    
//     float cam_world_width = 1.0;
//     float cam_world_height = cam_world_width * (float)w / (float)h;
//     float cam_focal_length = 2.5; 
//     Matrix4d cam_scale;
//     transforms_GetScalingMatrix4d(&cam_scale, cam_world_width, cam_world_height, cam_focal_length);
    
//     float cam_rot_x = 0;
//     Matrix4d cam_rotation_x;
//     transforms_GetRotationXMatrix4d(&cam_rotation_x, cam_rot_x);
    
//     float cam_rot_y = 0;
//     Matrix4d cam_rotation_y;
//     transforms_GetRotationYMatrix4d(&cam_rotation_y, cam_rot_y);
    
//     float cam_rot_z = 0; // 10.0 * M_PI / 180.0;
//     Matrix4d cam_rotation_z;
//     transforms_GetRotationZMatrix4d(&cam_rotation_z, cam_rot_z);

//     Matrix4d cam_transform = UNITY_TRANSFORM;
//     vecmath_MultiplyMatrix4d(&cam_transform, &cam_translate);
//     vecmath_MultiplyMatrix4d(&cam_transform, &cam_scale);
//     vecmath_MultiplyMatrix4d(&cam_transform, &cam_rotation_x);
//     vecmath_MultiplyMatrix4d(&cam_transform, &cam_rotation_y);
//     vecmath_MultiplyMatrix4d(&cam_transform, &cam_rotation_z);

//     Camera cam; // = { cam_transform, {0,0,-5,1}, {0,0,1,0}, {0,1,0,0}, {1,0,0,0}, 2.5, 1.0, w, h, 0, 0};
//     camera_Create(&cam, &cam_transform, w, h);

//     Ray ray = {{0,0,0,1},{0,0,0,0}}; 
    
//     Matrix4d sphere_transform;
//     Material mat;
//     ray_CreateDefaultMaterial(&mat);
//     Object sphere;
//     ray_CreateSphere(&sphere, &mat);
//     transforms_GetScalingMatrix4d(&sphere_transform, 1,1,1); 
//     vecmath_CopyMatrix4d(&sphere_transform, &(sphere.transform));
    
//     PointLight light;
//     Tuple4d lightPos = {-10, 10, -10, 1};
//     Color lightColor = {1, 1, 1};
//     ray_CreatePointLight(&light, &lightPos, &lightColor);

//     Object nothing = {OBJ_NONE, UNITY_TRANSFORM};
//     Intersection clostestHit = {0, nothing};
//     // Intersections ints = {{clostestHit}, 1};
//     Intersections ints = {{}, 0};

//     int x = 0;
//     int y = 0;
//     do
//     {
//         ints.count = 0;
//         clostestHit.object = nothing;
//         camera_CastRay(&cam, &ray, x, y);
//         ray_IntersectSphere(&ray, &sphere, &ints);
//         ray_Hit(&ints, &clostestHit);
//         if (clostestHit.object.type != OBJ_NONE)
//         {
//             Tuple4d hitPos, normal, eye;
//             ray_Position(&ray, &hitPos, clostestHit.t);
//             ray_NormalAt(&(clostestHit.object), &hitPos, &normal);
//             vecmath_CopyTuple4d(&(ray.direction), &eye);
//             vecmath_NormalizeTuple4d(&eye);
//             vecmath_ScaleTuple4d(&eye, -1.0);
//             Color color;
//             ray_Lighting(&color, &(clostestHit.object.material), &light, &hitPos, &eye, &normal);
            
//             canvas_DrawPixel(&canvas, &color, x, y);
//             //printf("r-");
//             clostestHit.object = nothing;
//             ints.intersections[0] = clostestHit;

//         }
//         else
//         {
//             canvas_DrawPixel(&canvas, &black, x, y);
//             //printf("B-");
//         }


//         x++;
//         if (x > cam.width-1)
//         {
//             x = 0;
//             y ++;
//             //printf("\n");
//         }
//     } while (y < cam.height);
//     canvas_PixelsToPPMFile(&canvas, "sphere.ppm");
//     canvas_Destroy(&canvas);    
// }


#endif // TEST
