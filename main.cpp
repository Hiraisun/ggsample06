// �E�B���h�E�֘A�̏���
#include "Window.h"

// �V�F�[�_�[�֘A�̏���
#include "shader.h"

// �W�����C�u����
#include <cmath>

// �A�j���[�V�����̎����i�b�j
const double cycle(5.0);

//
// ���C���v���O����
//
int main()
{
  // �E�B���h�E���쐬����
  Window window("ggsample06");

  // �w�i�F���w�肷��
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  // �v���O�����I�u�W�F�N�g�̍쐬
  const GLuint program(loadProgram("simple.vert", "pv", "simple.frag", "fc"));

  // in (attribute) �ϐ� cv �̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  const GLint cvLoc(glGetAttribLocation(program, "cv"));

  // uniform �ϐ��̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  const GLint mwLoc(glGetUniformLocation(program, "mw"));
  const GLint mcLoc(glGetUniformLocation(program, "mc"));
  const GLint mgLoc(glGetUniformLocation(program, "mg"));

  // �r���[�ϊ��s��� mv �ɋ��߂�
  const GgMatrix mv(ggLookat(0.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));

  // ���_�z��I�u�W�F�N�g�̍쐬
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // ���_�o�b�t�@�I�u�W�F�N�g�̍쐬
  GLuint vbo[2];
  glGenBuffers(2, vbo);

  // ���_�̍��W�l
  static const GLfloat pv[][3] =
  {
    { -1.0f, -0.8660254f, 0.0f },
    {  1.0f, -0.8660254f, 0.0f },
    {  0.0f,  0.8660254f, 0.0f }
  };

  // ���_�̐�
  static const int points(sizeof pv / sizeof pv[0]);

  // ���_�̍��W�l pv �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof pv, pv, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ� pv (index == 0) ����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // ���_�̐F
  static const GLfloat cv[][3] =
  {
    { 1.0f, 0.0f, 0.0f },  // ��
    { 0.0f, 1.0f, 0.0f },  // ��
    { 0.0f, 0.0f, 1.0f }   // ��
  };

  // ���_�̖@���x�N�g���i�h��p�j
  static const GLfloat nv[][3] =
  {
    { -0.086172748f, -0.049751860f, 0.99503719f },
    {  0.086172748f, -0.049751860f, 0.99503719f },
    {  0.0f, 0.099503719f, 0.99503719f }
  };

  // ���_�̐F cv �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  // �y�h��zcv �̑���� nv ���g���悤�ɕύX����
  glBufferData(GL_ARRAY_BUFFER, sizeof cv, cv, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ� cv (index == cvLoc) ����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(cvLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(cvLoc);

  // �o�ߎ��Ԃ̃��Z�b�g
  glfwSetTime(0.0);

  // �E�B���h�E���J���Ă���ԌJ��Ԃ�
  while (window.shouldClose() == GL_FALSE)
  {
    // �E�B���h�E����������
    glClear(GL_COLOR_BUFFER_BIT);

    // �V�F�[�_�v���O�����̎g�p�J�n
    glUseProgram(program);

    // �����̌v��
    const float t(static_cast<float>(fmod(glfwGetTime(), cycle) / cycle));

    // ���f���r���[�ϊ��s�� (���� t �ɂ��ƂÂ���]�A�j���[�V����)
    const GgMatrix mw(mv.rotateY(12.56637f * t));

    // �@���ϊ��s��
    const GgMatrix mg(mw.normal());

    // ���e�ϊ��s��
    const GgMatrix mp(ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f));

    // ���f���r���[�E���e�ϊ�
    const GgMatrix mc(mp * mw);

    // uniform �ϐ���ݒ肷��
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());

    // �`��Ɏg�����_�z��I�u�W�F�N�g�̎w��
    glBindVertexArray(vao);

    // �}�`�̕`��
    glDrawArrays(GL_TRIANGLES, 0, points);

    // ���_�z��I�u�W�F�N�g�̎w�����
    glBindVertexArray(0);

    // �V�F�[�_�v���O�����̎g�p�I��
    glUseProgram(0);

    // �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
    window.swapBuffers();
  }
}

