//
//  objloader.h
//  OpenGLModelLight
//
//  Created by Tim on 1/4/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __OpenGLModelLight__objloader__
#define __OpenGLModelLight__objloader__

bool objLoader(const char* objPath,
               std::vector<glm::vec3> & out_vertices,
               std::vector<glm::vec2> & out_uv,
               std::vector<glm::vec3> & out_normals);

void loadObjIndexed(const char* objPath,
              std::vector<unsigned int> & out_indices,
              std::vector<glm::vec3> & out_vertices,
              std::vector<glm::vec2> & out_uvs,
              std::vector<glm::vec3> & out_normals);

#endif /* defined(__OpenGLModelLight__objloader__) */
