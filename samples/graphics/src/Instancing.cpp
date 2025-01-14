#include "Instancing.h"
#include "SamplesGame.h"

#if defined(ADD_SAMPLE)
    ADD_SAMPLE("Graphics", "Instancing", Instancing, 3);
#endif

#include <bx/math.h>

static Mesh* createColoredCube(float size = 1.0f)
{
    float a = size;
    float vertices[] =
    {
        // position         // color
        -a, -a,  a,         0.0,  0.0,  1.0,  1.0f,
         a, -a,  a,         0.0,  0.0,  1.0,  1.0f,
        -a,  a,  a,         0.0,  0.0,  1.0,  1.0f,
         a,  a,  a,         0.0,  0.0,  1.0,  1.0f,
        -a,  a,  a,         0.0,  1.0,  0.0,  1.0f,
         a,  a,  a,         0.0,  1.0,  0.0,  1.0f,
        -a,  a, -a,         0.0,  1.0,  0.0,  1.0f,
         a,  a, -a,         0.0,  1.0,  0.0,  1.0f,
        -a,  a, -a,         0.0,  0.0,  1.0,  1.0f,
         a,  a, -a,         0.0,  0.0,  1.0,  1.0f,
        -a, -a, -a,         0.0,  0.0,  1.0,  1.0f,
         a, -a, -a,         0.0,  0.0,  1.0,  1.0f,
        -a, -a, -a,         0.0,  1.0,  0.0,  1.0f,
         a, -a, -a,         0.0,  1.0,  0.0,  1.0f,
        -a, -a,  a,         0.0,  1.0,  0.0,  1.0f,
         a, -a,  a,         0.0,  1.0,  0.0,  1.0f,
         a, -a,  a,         1.0,  0.0,  0.0,  1.0f,
         a, -a, -a,         1.0,  0.0,  0.0,  1.0f,
         a,  a,  a,         1.0,  0.0,  0.0,  1.0f,
         a,  a, -a,         1.0,  0.0,  0.0,  1.0f,
        -a, -a, -a,         1.0,  0.0,  0.0,  1.0f,
        -a, -a,  a,         1.0,  0.0,  0.0,  1.0f,
        -a,  a, -a,         1.0,  0.0,  0.0,  1.0f,
        -a,  a,  a,         1.0,  0.0,  0.0,  1.0f,
    };
    short indices[] =
    {
        0, 1, 2,
        2, 1, 3,
        4, 5, 6,
        6, 5, 7,
        8, 9, 10,
        10, 9, 11,
        12, 13, 14,
        14, 13, 15,
        16, 17, 18,
        18, 17, 19,
        20, 21, 22,
        22, 21, 23
    };
    unsigned int vertexCount = 24;
    unsigned int indexCount = 36;
    VertexFormat::Element elements[] =
    {
        VertexFormat::Element(VertexFormat::POSITION, 3),
        VertexFormat::Element(VertexFormat::COLOR, 4),
    };
    Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 2), vertexCount, false);
    if (mesh == NULL)
    {
        GP_ERROR("Failed to create mesh.");
        return NULL;
    }
    mesh->setVertexData(vertices, 0, vertexCount);
    MeshPart* meshPart = mesh->addPart(Mesh::TRIANGLES, Mesh::INDEX16, indexCount, false);
    meshPart->setIndexData(indices, 0, indexCount);
    return mesh;
}

static Mesh* createTexturedCube(float size = 1.0f)
{
    float a = size;
    float vertices[] =
    {
         // position     // normal              // texcoord
        -a, -a,  a,      0.0,  0.0,  1.0,       0.0, 0.0,
         a, -a,  a,      0.0,  0.0,  1.0,       1.0, 0.0,
        -a,  a,  a,      0.0,  0.0,  1.0,       0.0, 1.0,
         a,  a,  a,      0.0,  0.0,  1.0,       1.0, 1.0,
        -a,  a,  a,      0.0,  1.0,  0.0,       0.0, 0.0,
         a,  a,  a,      0.0,  1.0,  0.0,       1.0, 0.0,
        -a,  a, -a,      0.0,  1.0,  0.0,       0.0, 1.0,
         a,  a, -a,      0.0,  1.0,  0.0,       1.0, 1.0,
        -a,  a, -a,      0.0,  0.0, -1.0,       0.0, 0.0,
         a,  a, -a,      0.0,  0.0, -1.0,       1.0, 0.0,
        -a, -a, -a,      0.0,  0.0, -1.0,       0.0, 1.0,
         a, -a, -a,      0.0,  0.0, -1.0,       1.0, 1.0,
        -a, -a, -a,      0.0, -1.0,  0.0,       0.0, 0.0,
         a, -a, -a,      0.0, -1.0,  0.0,       1.0, 0.0,
        -a, -a,  a,      0.0, -1.0,  0.0,       0.0, 1.0,
         a, -a,  a,      0.0, -1.0,  0.0,       1.0, 1.0,
         a, -a,  a,      1.0,  0.0,  0.0,       0.0, 0.0,
         a, -a, -a,      1.0,  0.0,  0.0,       1.0, 0.0,
         a,  a,  a,      1.0,  0.0,  0.0,       0.0, 1.0,
         a,  a, -a,      1.0,  0.0,  0.0,       1.0, 1.0,
        -a, -a, -a,     -1.0,  0.0,  0.0,       0.0, 0.0,
        -a, -a,  a,     -1.0,  0.0,  0.0,       1.0, 0.0,
        -a,  a, -a,     -1.0,  0.0,  0.0,       0.0, 1.0,
        -a,  a,  a,     -1.0,  0.0,  0.0,       1.0, 1.0
    };
    short indices[] =
    {
        0, 1, 2,
        2, 1, 3,
        4, 5, 6,
        6, 5, 7,
        8, 9, 10,
        10, 9, 11,
        12, 13, 14,
        14, 13, 15,
        16, 17, 18,
        18, 17, 19,
        20, 21, 22,
        22, 21, 23
    };
    unsigned int vertexCount = 24;
    unsigned int indexCount = 36;
    VertexFormat::Element elements[] =
    {
        VertexFormat::Element(VertexFormat::POSITION, 3),
        VertexFormat::Element(VertexFormat::NORMAL, 3),
        VertexFormat::Element(VertexFormat::TEXCOORD0, 2)
    };
    Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 3), vertexCount, false);
    if (mesh == NULL)
    {
        GP_ERROR("Failed to create mesh.");
        return NULL;
    }
    mesh->setVertexData(vertices, 0, vertexCount);
    MeshPart* meshPart = mesh->addPart(Mesh::TRIANGLES, Mesh::INDEX16, indexCount, false);
    meshPart->setIndexData(indices, 0, indexCount);
    return mesh;
}


Instancing::Instancing()
    : _font(NULL), _model(NULL)
{    
    _materialColored = nullptr;
    _materialTextured = nullptr;
    _form = nullptr;
    _rotValue = 0.0f;
    _maxDimensions = 20;
}

void Instancing::setColoredGeometry()
{
    GP_ASSERT(_materialColored);

    SAFE_RELEASE(_model);

    Mesh* mesh = createColoredCube();
    _model = Model::create(mesh);
    _model->setMaterial(_materialColored);

    SAFE_RELEASE(mesh);
}

void Instancing::setTexturedGeometry()
{
    GP_ASSERT(_materialTextured);

    SAFE_RELEASE(_model);

    Mesh* mesh = createTexturedCube();
    _model = Model::create(mesh);
    _model->setMaterial(_materialTextured);

    SAFE_RELEASE(mesh);
}

void Instancing::initialize()
{
    // Create the font for drawing the framerate.
    _font = Font::create("res/core/ui/arial.gpb");

    // Create a perspective projection matrix.
    float ratio = getWidth() / (float)getHeight();
    Matrix::createPerspective(45.0f, ratio, 1.0f, 1000.0f, &_worldViewProjectionMatrix);

    // Create a lookat matrix and multiply with projection matrix.
    Matrix dst;
    Vector3 eye(-80,80,-180);
    Vector3 targetPos(0,0,0);
    Vector3 up(0,1,0);
    Matrix::createLookAt(eye, targetPos, up, &dst);
    _worldViewProjectionMatrix = _worldViewProjectionMatrix * dst;

    // Create a material from the built-in "colored-unlit" vertex and fragment shaders.
    _materialColored = Material::create("res/core/shaders/forward/colored.vert", "res/core/shaders/forward/colored.frag", "VERTEX_COLOR;INSTANCED");
    _materialColored->getStateBlock()->setCullFace(true);
    _materialColored->getStateBlock()->setDepthTest(true);
    _materialColored->getStateBlock()->setDepthWrite(true);

    // Create a material with texture
    _materialTextured = Material::create("res/core/shaders/forward/textured.vert", "res/core/shaders/forward/textured.frag", "INSTANCED");
    Texture::Sampler * sampler = Texture::Sampler::create("res/data/textures/dirt.png");
    _materialTextured->getParameter("u_diffuseTexture")->setValue(sampler);
    _materialTextured->getStateBlock()->setCullFace(true);
    _materialTextured->getStateBlock()->setDepthTest(true);
    _materialTextured->getStateBlock()->setDepthWrite(true);

    // Set colored cube at init.
    setColoredGeometry();

    // initialise UI
    initializeUI();
}

void Instancing::initializeUI()
{
    Theme::Style* style = Theme::getDefault()->getEmptyStyle();

    _form = Form::create("Form", style);
    _form->setLayout(Layout::LAYOUT_VERTICAL);
    _form->setWidth(200);
    _form->setAlignment(Control::Alignment::ALIGN_VCENTER_LEFT);

    Slider * slider = Slider::create("slider_maxdim");
    slider->setText("Dimensions");
    slider->setValueTextVisible(true);
    slider->setWidth(190);
    slider->setMin(1);
    slider->setMax(40);
    slider->setValue(_maxDimensions);
    slider->addListener(this, Control::Listener::VALUE_CHANGED);

    RadioButton * radio1 = RadioButton::create("radio_colored");
    radio1->setText("Colored");
    radio1->setSelected(true);
    radio1->addListener(this, Control::Listener::CLICK);

    RadioButton * radio5 = RadioButton::create("radio_textured");
    radio5->setText("Textured");
    radio5->setSelected(false);
    radio5->addListener(this, Control::Listener::CLICK);

    _form->addControl(slider);
    _form->addControl(radio1);
    _form->addControl(radio5);
}

void Instancing::finalize()
{
    SAFE_RELEASE(_model);
    SAFE_RELEASE(_materialColored);
    SAFE_RELEASE(_materialTextured);
    SAFE_RELEASE(_font);
    SAFE_RELEASE(_form);
}

void Instancing::update(float elapsedTime)
{
    _rotValue += MATH_PI * elapsedTime * 0.001f;
}

void Instancing::render(float elapsedTime)
{
    if(_model)
    {
        // 80 bytes stride = 64 bytes for 4x4 matrix + 16 bytes for RGBA color.
        const uint16_t instanceStride = sizeof(Matrix) + sizeof(Vector4);

        // instanced cubes
        const uint32_t numInstances = _maxDimensions*_maxDimensions*_maxDimensions;

        if (numInstances == bgfx::getAvailInstanceDataBuffer(numInstances, instanceStride) )
        {
            bgfx::InstanceDataBuffer idb;
            bgfx::allocInstanceDataBuffer(&idb, numInstances, instanceStride);
            uint8_t* data = idb.data;

            const float step = 3.0f;
            float pos[3];
            pos[0] = -step*_maxDimensions / 2.0f;
            pos[1] = -step*_maxDimensions / 2.0f;
            pos[2] = -15.0;

            static float time = 0.0f;
            time += elapsedTime * 0.001f;

            for(int x=0; x<_maxDimensions; ++x)
                for(int y=0; y<_maxDimensions; ++y)
                    for(int z=0; z<_maxDimensions; ++z)
                    {
                        Matrix* mtx = (Matrix*)data;
                        mtx->setIdentity();
                        mtx->translate(Vector3( pos[0] + float(x)*step,
                                                pos[1] + float(y)*step,
                                                pos[2] + float(z)*step));
                        mtx->rotate(Quaternion(Vector3(time + x*0.21f,
                                                       time + y*0.37f,
                                                       time + z*0.13f),
                                               time));

                        Vector4 * color = (Vector4*)&data[64];
                        color->x = sin(float(x)/11.0f)*0.5f+0.5f * 255.0f;
                        color->y = cos(float(y)/11.0f)*0.5f+0.5f * 255.0f;
                        color->z = sin(3.0f)*0.5f+0.5f * 255.0f;
                        color->w = 1.0f;

                        data += instanceStride;
                    }

                // Set instance data buffer.
                bgfx::setInstanceDataBuffer(&idb);

                // Submit draw
                _model->getMaterial()->getParameter("u_worldViewProjectionMatrix")->setValue(_worldViewProjectionMatrix);
                _model->draw();
        }
    }

    drawFrameRate(_font, Vector4(0, 0.5f, 1, 1), 5, getHeight()-20, getFrameRate());

    _form->draw();
}

void Instancing::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
    case Touch::TOUCH_PRESS:        
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}

void Instancing::controlEvent(Control* control, EventType evt)
{
    Button* button = static_cast<Button*>(control);

    if (strcmp(button->getId(), "radio_colored") == 0)
    {
        setColoredGeometry();
    }
    else if (strcmp(button->getId(), "radio_textured") == 0)
    {
        setTexturedGeometry();
    }
    else if (strcmp(button->getId(), "slider_maxdim") == 0)
    {
        Slider* slider = static_cast<Slider*>(control);
        _maxDimensions = slider->getValue();
    }
}
