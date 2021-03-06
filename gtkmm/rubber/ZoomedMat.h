//
// Created by Oleksiy Grechnyev on 12/20/17.
//

#pragma once

#include <vector>

#include <opencv2/core.hpp>
#include <gdkmm/window.h>

/** @brief OpenCV Mat original and scaled version
 *
 */
class ZoomedMat {
public: //=========== Methods ================
    /// Generate scaledImg using current scale
    void rescale();

    /// Get a Pixbuf  from scaledImg (not valid after each rescale !), with rubber etc.
    Glib::RefPtr<Gdk::Pixbuf> createPixbuf();

    /// Load origImg from file
    void fromFile(const std::string & fileName);

    /// Draw a rubber band
    void drawRubber(int x1, int y1, int x2, int y2);

    /// Remove a rubber band
    void removeRubber();

    /// Get the subimage defined by the rubber
    cv::Mat getSubImage();

    const cv::Mat &getOrigImg() const {
        return origImg;
    }

    void setOrigImg(const cv::Mat &origImg) {
        ZoomedMat::origImg = origImg;
        rescale();
    }

    const cv::Mat &getScaledImg() const {
        return scaledImg;
    }


    double getScale() const {
        return scale;
    }

    void setScale(double scale) {
        ZoomedMat::scale = scale;
        rescale();
    }

    bool getIsRubber() const{
        return isRubber;
    }

    const std::vector<cv::Rect> & getRegions() const
    {
        return regions;
    }

    /// Set regions, creates scaled versions as well
    void setRegions(const std::vector<cv::Rect> &regions);

private:  //========== Methods ===============
    /// Create scaledImg from scaledImg0 with the rubber band and regions
    void drawRects();

    /// Check that the point is in the boundaries of an image
    static cv::Point checkEdges(const cv::Point & p, const cv::Mat & m);

private:  //========== Fields ================
    /// The original image (in BGR)
    cv::Mat origImg;

    /// The scaled image (in RGB), with ruber band possibly
    cv::Mat scaledImg;

    /// The scaled image (in RGB), with no rubber band
    cv::Mat scaledImg0;

    /// The scale
    double scale = 1.0;

    /// Do we have a rubber band ?
    bool isRubber = false;

    /// Rubber band two corners
    cv::Point p1, p2;

    /// Selected regions, orig image
    std::vector <cv::Rect> regions;

    /// Selected regions, scaled to the size of scaledImg
    std::vector <cv::Rect> regionsScaled;
};



