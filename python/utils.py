import numpy as np
def apply_homo_transform(point_cloud, matrix):
    assert point_cloud.shape[1] == 3, "point cloud should be 3 in dim "
    pc = np.concatenate([point_cloud, np.ones((point_cloud.shape[0], 1))], 1)
    return matrix.dot(pc.T).T[:, :3]

def get_submesh_by_vertices(mesh, vertices, logic="and"):
    if logic == "and":
        valid_face = np.array([i for i, f in enumerate(mesh.faces) if \
                               f[0] in vertices and f[1] in vertices and f[2] in vertices])
    else:
        valid_face = np.array([i for i, f in enumerate(mesh.faces) if \
                               f[0] in vertices or f[1] in vertices or f[2] in vertices])
    submesh = mesh.submesh([valid_face])[0]
    return submesh

if __name__ == "__main__":
    pc = np.random.rand(5,3)
    matrix = np.random.rand(4,4)
    print(apply_homo_transform(pc, matrix))
