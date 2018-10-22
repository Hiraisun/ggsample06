#version 150 core

// ����
const vec4 pl     = vec4(0.0, 0.0, 1.0, 0.0);       // �ʒu
const vec4 lamb   = vec4(0.2, 0.2, 0.2, 1.0);       // ���������̋��x
const vec4 ldiff  = vec4(1.0, 1.0, 1.0, 0.0);       // �g�U���ː����̋��x
const vec4 lspec  = vec4(1.0, 1.0, 1.0, 0.0);       // ���ʔ��ː����̋��x

// �ގ�
const vec4 kamb   = vec4(0.6, 0.0, 0.0, 1.0);       // �����̔��ˌW��
const vec4 kdiff  = vec4(0.6, 0.0, 0.0, 1.0);       // �g�U���ˌW��
const vec4 kspec  = vec4(0.4, 0.4, 0.4, 1.0);       // ���ʔ��ˌW��
const float kshi  = 80.0;                           // �P���W��

// ���_����
in vec4 pv;                                         // ���[�J�����W�n�̒��_�ʒu
in vec4 cv;                                         // ���_�̐F �� main.cpp �ł���ɖ@���x�N�g�� nv ������

// �ϊ��s��
uniform mat4 mw;                                    // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;                                    // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;                                    // �@���x�N�g���̕ϊ��s��

// ���X�^���C�U�ɑ��钸�_����
out vec4 vc;                                        // ���_�F

void main(void)
{
  // ���_���W�n�ł͎��_�͌��_�ɂ���̂ŁC�����x�N�g���͒��_���猴�_�Ɍ������x�N�g���ł���
  vec4 p = mw * pv;                                 // ���_���W�n�̒��_�̈ʒu
  vec3 v = -normalize(p.xyz / p.w);                 // �����x�N�g��
  vec3 l = normalize((pl * p.w - p * pl.w).xyz);    // �����x�N�g��
  vec3 n = normalize((mg * cv).xyz);                // �@���x�N�g��

  //�y�h��z���̂P�s�i�̉E�Ӂj��u�������Ă�������
  vc = cv;

  gl_Position = mc * pv;
}
