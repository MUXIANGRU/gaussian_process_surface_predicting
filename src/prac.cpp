#include<iostream>
#include"gaussian_process_regression/gaussian_process_regression.h"
#include<ros/ros.h>
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>
#include<string>
#include<Eigen/Core>

double length_scale ;
double sigma_f ;
double sigma_n ;
const size_t input_dim(72), output_dim(36);
typedef Eigen::Matrix<float,72,1> input_type;
typedef Eigen::Matrix<float,36,1> output_type;
std::vector<input_type> train_inputs, test_inputs;
std::vector<output_type> train_outputs, test_outputs;
GaussianProcessRegression<float> myGPR(input_dim, output_dim);


template<typename input_type, typename output_type>
void load_data(const char *fname, std::vector<input_type> &inputs, std::vector<output_type> &outputs, int input_dim, int output_dim) {
  std::cout<<"entry this branch........"<<std::endl;
  input_type inp,tinp;
  output_type outp,toutp;
  std::ifstream myfile(fname);
  if (!myfile.is_open())
  {
      std::cout << "打开文件失败" << std::endl;
      return;
  }
  //ASSERT_TRUE(bool(myfile));
  std::string line;
  while(getline(myfile,line)){
      std::cout<<line<<" ";
    std::istringstream line_stream(line);
    for(size_t k = 0; k < input_dim; k++)
      line_stream>>inp(k);
    for(size_t k = 0; k < output_dim; k++)
      line_stream>>outp(k);
    inputs.push_back(inp);
    outputs.push_back(outp);
  }
  std::cout<<"finish loading..."<<std::endl;
}
template<typename R>
void set_hyperparameters_from_file(const char *fname, GaussianProcessRegression<R> & gpr) {
  std::ifstream myfile;
  myfile.open(fname);
  if (!myfile.is_open())
  {
      std::cout << "打开文件失败" << std::endl;
      return;
  }
  //ASSERT_TRUE(bool(myfile));
  R l, f, n;
  myfile>>l>>f>>n;
  //std::cout<<l<<" "<<f<<" "<<n<<std::endl;
  myfile.close();
  gpr.SetHyperParams(l,f,n);
}

int main(int argc, char **argv){
    ros::init (argc, argv, "prac");
    ros::NodeHandle ph;
    //why the gpr is not defined while out of the main() function???
    //myGPR.SetHyperParams(length_scale, sigma_f, sigma_n);
    set_hyperparameters_from_file("/home/mxr/catkin_gpr/src/gaussian_process_regression/config/hyperparam.txt", myGPR);
    //myGPR.GetHyperParams(length_scale,sigma_f,sigma_n);
    load_data("/home/mxr/catkin_gpr/src/gaussian_process_regression/config/train_data.txt",train_inputs,train_outputs,72,36);
    for(int i=0;i<train_outputs.size();i++){
        std::cout<<train_outputs[i]<<" ";
    }
    std::cout<<"##################"<<std::endl;
    for(int i=0;i<train_inputs.size();i++){
        std::cout<<train_inputs[i]<<"%";
    }

    for(size_t k=0; k<train_inputs.size(); k++){
      myGPR.AddTrainingData(train_inputs[k], train_outputs[k]);
    }
    load_data("/home/mxr/catkin_gpr/src/gaussian_process_regression/config/test_data.txt",test_inputs,test_outputs,72,36);
    double threshold = 0.1;
    std::cout<<"THE test data is :"<<std::endl;
    for(int i=0;i<test_inputs.size();i++){
        std::cout<<test_inputs[i]<<" ";
    }

    for(size_t k=0; k<test_inputs.size(); k++){
      auto outp = myGPR.DoRegression(test_inputs[k]);
      std::cout<<outp<<std::endl;
//      for (size_t l=0; l < outp.rows(); ++l)
//        {
//      ASSERT_NEAR(test_outputs[k](l), outp(l), threshold);
//        }
    }

    //std::cout<<outp<<std::endl;

    // add some training data
//    int n_train = 100;
//    for(int k=0; k<n_train; k++){
//        train_input.setRandom();
//        train_output.setRandom();
//        myGPR.AddTrainingData(train_input,train_output);
//    }
//    Eigen::VectorXf test_input(input_dim);
//    Eigen::VectorXf test_output(output_dim);
//    test_input.setRandom();
//    test_output = myGPR.DoRegression(test_input);

    //ros::spin();

    return 0;
};
