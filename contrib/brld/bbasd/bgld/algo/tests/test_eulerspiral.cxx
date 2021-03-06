// This is bbasd/bgld/algo/tests/test_eulerspiral.cxx

#include <testlib/testlib_test.h>
#include <bgld/algo/bgld_eulerspiral.h>
#include <vcl_iostream.h>
#include <vcl_cmath.h>
#include <vnl/vnl_math.h>
#include <vsl/vsl_vector_io.h>
#include <vsl/vsl_binary_io.h>
#include <vcl_vector.h>
#include <vcl_cstdlib.h>
#include <vcl_string.h>
#include <vnl/algo/vnl_levenberg_marquardt.h>


//: Test functions of eulerspiral class
MAIN( test_eulerspiral )
{ 
  double tolerance = 1e-4;
  bool test_passed;
  // -------------- INITIALIZERS/CONSTRUCTORS/DESTRUCTORS ----------------------------    
  // Default
  START (" Test bgld_eulerspiral class");
  vcl_cout << "Test Constructors" << vcl_endl;
  bgld_eulerspiral es1 = bgld_eulerspiral();
  TEST("Default Constructor", &es1 != 0, true);
  
  // construct from intrinsic params
  bgld_eulerspiral es2 = bgld_eulerspiral(vgl_point_2d< double >(0, 0), 0.0, 1, 1, 2);
  test_passed = (vcl_fabs(es2.start().x() - 0) < tolerance) &&
     (vcl_fabs(es2.start().y() - 0) < tolerance) && 
     (vcl_fabs(es2.start_angle() - 0) < tolerance) &&
     (vcl_fabs(es2.k0() - 1) < tolerance) && 
     (vcl_fabs(es2.gamma() - 1) < tolerance) && 
     (vcl_fabs(es2.length() - 2) < tolerance);
  TEST("Contruct from intrinsic params", test_passed, true);
  
  // contruct from 2 point-tangents
  bgld_eulerspiral es3 = bgld_eulerspiral(vgl_point_2d< double >(0, 0), 0, 
    vgl_point_2d< double >(5, 5), vnl_math::pi_over_2);
  test_passed = (vcl_fabs(es3.gamma() - 0) < tolerance) &&
    (vcl_fabs(es3.k0() - 0.2) < tolerance);
  es3.print(vcl_cout);
  TEST("Construct from two point-tangents", test_passed, true);

  // copy contructor
  bgld_eulerspiral es4 = bgld_eulerspiral(es3);
  test_passed = (es3.start() == es4.start()) &&
    (es3.start_angle() == es4.start_angle()) &&
    (es3.k0() == es4.k0()) &&
    (es3.gamma() == es4.gamma());
  TEST("Copy contructor" , test_passed, true);

  // MEMBER ACCESS FUNCTIONS
  vcl_cout << "Test accesing member variables" << vcl_endl;
  // test set_starting_angle (converted to [0, 2*pi))
  es3.set_start_angle(7);
  TEST("Set start angle", es3.start_angle() == (7-2*vnl_math::pi), true);
  // test init function
  es3.init(vgl_point_2d< double >(1, 1), vnl_math::pi / 6, 0.2, 0.05, 2); 
  test_passed = (vcl_fabs(es3.start().x() - 1) < tolerance) &&
     (vcl_fabs(es3.start().y() - 1) < tolerance) && 
     (vcl_fabs(es3.start_angle() - vnl_math::pi/6) < tolerance) &&
     (vcl_fabs(es3.k0() - 0.2) < tolerance) && 
     (vcl_fabs(es3.gamma() - 0.05) < tolerance) && 
     (vcl_fabs(es3.length() - 2) < tolerance);
  TEST("init(...) function", test_passed, true);

  // test set intrinsic and extrinsic params functions
  es2.set_extrinsic_params(vgl_point_2d< double >(1, 1), 1);
  es2.set_intrinsic_params(0.2, 0.5, 4);
  test_passed = (vcl_fabs(es2.start().x() - 1) < tolerance) &&
     (vcl_fabs(es2.start().y() - 1) < tolerance) && 
     (vcl_fabs(es2.start_angle() - 1) < tolerance) &&
     (vcl_fabs(es2.k0() - 0.2) < tolerance) && 
     (vcl_fabs(es2.gamma() - 0.5) < tolerance) && 
     (vcl_fabs(es2.length() - 4) < tolerance);

  TEST("set_intrinsic_params() and set_extrinsic_params()", test_passed, true);

  vcl_cout << "Test creating Euler spiral from 2 point-tangents" << vcl_endl;
  // data structure: case = [x0, y0, t0 (radian), x1, y1, t1(radian)]
  // result = [k0, gamma, len]
  // a straight line
  double case1[] = {1, 1, 0, 6, 1, 0};   
  double result1[] = {0, 0, 5};
  // a circle
  double case2[] = {0, 0, 0, 5, 5, vnl_math::pi_over_2};
  double result2[] = {0.2, 0, 7.85398163397448};
  // an Euler spiral with no inflection point
  double case3[] = {0, 0, 0, 1.958976835, 0.3293727655, 0.4};
  double result3[] = {0.1, 0.1, 2};
  // an Euler spiral with no inflection point - negative curvature
  double case4[] = {0, 0, 0, 1.916086763, -.4545589288, -0.6};
  double result4[] = {-0.1, -0.2, 2};
  // Euler spiral with inflection point
  double case5[] = {0, 0, 0, 1.994674276, -0.15215044e-3, .2000000000};
  double result5[] = {-0.2, 0.3, 2};


  bgld_eulerspiral es;
  
  // test case 1 - create a "straight line" eulerspiral
  test_passed = true;
  es.set_params(vgl_point_2d< double >(case1[0], case1[1]), case1[2], 
    vgl_point_2d<double >(case1[3], case1[4]), case1[5]);
  es.compute_es_params();
  double r1[] = {es.k0(), es.gamma(), es.length()};
  test_passed = true;
  for (int i = 0; i < 3; i ++){
    if (vcl_fabs(r1[i] - result1[i]) > tolerance)
      test_passed = false;
  }
  TEST("Straight-line Euler spiral", test_passed, true);

    // test case 2 - create a "circular" eulerspiral
  test_passed = true;
  es.compute_es_params(vgl_point_2d< double >(case2[0], case2[1]), case2[2], 
    vgl_point_2d<double >(case2[3], case2[4]), case2[5]);
  double r2[] = {es.k0(), es.gamma(), es.length()};
  test_passed = true;
  for (int i = 0; i < 3; i ++){
    if (vcl_fabs(r2[i] - result2[i]) > tolerance)
      test_passed = false;
  }
  TEST("Circular Euler spiral", test_passed, true);

  // test case 3 - create an eulerspiral with no inflection point
  test_passed = true;
  es.compute_es_params(vgl_point_2d< double >(case3[0], case3[1]), case3[2], 
    vgl_point_2d<double >(case3[3], case3[4]), case3[5]);
  double r3[] = {es.k0(), es.gamma(), es.length()};
  test_passed = true;
  for (int i = 0; i < 3; i ++){
    if (vcl_fabs(r3[i] - result3[i]) > tolerance)
      test_passed = false;
  }
  TEST("Euler spiral with no inflection point", test_passed, true);

  // test case 4 - create an eulerspiral with no inflection point and with negative curvature
  test_passed = true;
  es.compute_es_params(vgl_point_2d< double >(case4[0], case4[1]), case4[2], 
    vgl_point_2d<double >(case4[3], case4[4]), case4[5]);
  double r4[] = {es.k0(), es.gamma(), es.length()};
  test_passed = true;
  for (int i = 0; i < 3; i ++){
    if (vcl_fabs(r4[i] - result4[i]) > tolerance)
      test_passed = false;
  }
  TEST("No inflection point, negative curvature", test_passed, true);
  

  // test case 5 - create an eulerspiral with inflection point
  test_passed = true;
  es.compute_es_params(vgl_point_2d< double >(case5[0], case5[1]), case5[2], 
    vgl_point_2d<double >(case5[3], case5[4]), case5[5]);
  double r5[] = {es.k0(), es.gamma(), es.length()};
  test_passed = true;
  for (int i = 0; i < 3; i ++){
    if (vcl_fabs(r5[i] - result5[i]) > tolerance)
      test_passed = false;
  }
  TEST("Euler spiral with inflection point", test_passed, true);

  // test geometry functions - using case5 information
  vcl_cout << " Test geometry functions" << vcl_endl;
  double s1 = 1.37;
  vgl_point_2d<double > p1(1.368419857, -0.5909225611e-1);
  vgl_vector_2d< double > v1(vcl_cos(0.75350000e-2), vcl_sin(0.75350000e-2));
  double k1 = .211;

  // test point_at(s) function
  test_passed = vcl_fabs(es.point_at_length(s1).x() - p1.x()) < tolerance &&
    vcl_fabs(es.point_at_length(s1).y() - p1.y()) < tolerance;
  vcl_cout << "x = " << es.point_at_length(s1).x() << vcl_endl;
  vcl_cout << "y = " << es.point_at_length(s1).y() << vcl_endl;
  TEST("Test point_at_length(s) function", test_passed, true);
  // test tangent_at_length(s) function
  test_passed = vcl_fabs(es.tangent_at_length(s1).x() - v1.x()) < tolerance &&
    vcl_fabs(es.tangent_at_length(s1).y() - v1.y()) < tolerance;
  //vcl_cout << "Tangent x = " << es.tangent_at_length(s1).x() << "\t v1.x() = " << v1.x() << vcl_endl;
  //vcl_cout << "Tangent y = " << es.tangent_at_length(s1).y() << "\t v1.y() = " << v1.y() << vcl_endl;
  TEST("Test tangent_at_length(s) function", test_passed, true);
  // test curvature_at_length(s) function
  test_passed = vcl_fabs(es.curvature_at_length(s1)- k1) < tolerance;
  TEST("Test curvature_at_length(s) function", test_passed, true);
  

  // bool success = bgld_eulerspiral_lookup_table::instance()->has_table();
  // vcl_cout << "success = " << success << vcl_endl;     
    //k0(CCW(params.psi, params.start_angle), CCW(params.psi, params.end_angle));
  vcl_vector< double > g;
  for (int i = 0; i < 10; i ++){
    es.set_params(vgl_point_2d< double >(0, 0), 0, 
      vgl_point_2d<double >(1, 0), vnl_math::pi / 10.0 * i);
    es.compute_es_params();
    g.push_back(es.length());
  }


  vcl_cout << vcl_endl << "Example using eulerspiral look-up table " << vcl_endl;
  double s2 = vnl_math::pi*2+ 1.1;
  double e2 = 0.5 - vnl_math::pi*2;
  es.compute_es_params(vgl_point_2d< double >(0, 0), s2, vgl_point_2d< double >(1, 0), e2);
  es.print(vcl_cout);
  
  if (bgld_eulerspiral_lookup_table::instance()->has_table()){
    double k0_new, gamma_new, len_new, k0_max_error_new, gamma_max_error_new, len_max_error_new ;
    bgld_eulerspiral_lookup_table::instance()->look_up(s2, e2, &k0_new, &gamma_new, &len_new, 
      &k0_max_error_new, &gamma_max_error_new, &len_max_error_new);
    vcl_cout << "Data from look-up table : " << vcl_endl;
    vcl_cout << "k0_new = " << k0_new << vcl_endl;
    vcl_cout << "gamma_new = " << gamma_new << vcl_endl;
    vcl_cout << "len_new = " << len_new << vcl_endl;
    test_passed = (vcl_abs(es.k0()-k0_new) + vcl_abs(es.gamma()-gamma_new) + 
      vcl_abs(es.length()-len_new)) < 1e-2;
    TEST("Test look-up table validity", test_passed, true);
  }
  else
    vcl_cout << "no table" << vcl_endl;

  vcl_cout << "Comparing between levenberg_marquardt minimization and simple gradient descent" << vcl_endl;

  test_passed = true;
  // use vnl_levenberg_marquardt
  es.compute_es_params(vgl_point_2d< double >(case3[0], case3[1]), case3[2], 
    vgl_point_2d<double >(case3[3], case3[4]), case3[5]);
  double x_1[] = {es.k0(), es.gamma(), es.length()};
  vcl_cout << vcl_endl << "Use Levenberg-Marquart" ;
  es.print(vcl_cout);
  // use simple gradient descent
  es.compute_es_params(true, false);
  double x_2[] = {es.k0(), es.gamma(), es.length()};
  vcl_cout << vcl_endl << "use simple gradient descent " ;
  es.print(vcl_cout);

  test_passed = vcl_fabs(x_1[0]-x_2[0]) < tolerance && 
    vcl_fabs(x_1[1]-x_2[1]) < tolerance && 
    vcl_fabs(x_1[2]-x_2[2]) < tolerance;
  vcl_cout << vcl_endl;
  TEST("Match results between levenberg_marquardt and simple gradient descent", test_passed, true);

  //// test Ric's case where returned gamma does not match with expected gamma
  ////// These points are samples of an ellipse.
  //// expected gamma = -0.050989
  //// computed gamma = 0.005680114857569251718416581
  //vgl_point_2d<double > t0(60.84694743164385499767377, 89.89220835656487906817347);
  //vgl_point_2d<double > t1(60.82701761213060365207639, 89.89723025337016792946088);
  //double angle0 = 2.891911379829834594090698;   
  //double angle1 = 2.89759298672725584822274;

  //es.compute_es_params(t0, angle0, t1, angle1);
  //es.print(vcl_cout);

  //int prec = vcl_cout.precision();
  //vcl_cout << "Precision = " << prec << vcl_endl;
  //vcl_cout.precision(15);
  //es.print(vcl_cout);
  //vcl_cout.precision(prec);
  

  

  

  SUMMARY();
}
